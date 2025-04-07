#include "CCollisionManager.h"
#include "CSceneManager.h"
#include "CQuadTreeManager.h"
#include "CTimeManager.h"

#include "CLayer.h"
#include "CActor.h"

#include "CTransformComponent.h"
#include "CColliderComponent.h"
#include "CObjectManager.h"
#include "CApplication.h"
//#include 
extern Framework::CApplication application;

namespace Framework
{
	//std::bitset<(UINT)Enums::eLayerType::Size> CCollisionManager::m_bsCollisionCheck[(UINT)Enums::eLayerType::Size] = {false};

	//std::vector<std::vector<bool>>		CCollisionManager::m_vectorCollisionCheck	= {};
	std::unordered_map<UINT64, bool>	CCollisionManager::m_unmapCollisions		= {};
	std::vector<CColliderComponent*>	CCollisionManager::m_vecCollider			= {};
	bool* CCollisionManager::m_bArryCollision = nullptr;
	INT CCollisionManager::m_iCollTickComponentFPS = 0;

	CCollisionManager::CCollisionManager()	//사용안함
	{	}
	CCollisionManager::~CCollisionManager() //사용안함
	{	}

	void CCollisionManager::InitCollisionLayer()
	{
		if (m_bArryCollision != nullptr)
		{	return;		}

		const UINT size = OBJECT::GetLayerSize();
		const UINT fullSize = size * size;
		m_bArryCollision = new bool [fullSize];
		memset(m_bArryCollision, 0, sizeof(bool) * fullSize);

	}

	void CCollisionManager::ClearActor()
	{
		SCENE::Destroy();
	}

	void CCollisionManager::SetCollisionLayerState(UINT left, UINT right, bool enable)
	{
		const UINT size = OBJECT::GetLayerSize();
		if (left > size || right > size ||
			m_bArryCollision == nullptr)
		{
			assert(1);
			return;
		}

		UINT row, col;
		if (left <  right)
		{
			row = left;
			col = right;
		}
		else
		{
			col = left;
			row = right;
		}
		m_bArryCollision[(row * size) + col] = enable;
	}

	const std::vector<CColliderComponent*>& CCollisionManager::GetCollisionCollider(const Maths::Vector2& center, const Maths::Vector2& size)
	{
		return CQuadTreeManager::Query(center, size);
	}

	const std::vector<CColliderComponent*>& CCollisionManager::GetCollisionCollider(const Rect& rect)
	{
		const Maths::Vector2 center	= (rect.max + rect.min) * 0.5f;
		const Maths::Vector2 size		=  rect.max - rect.min;

		return GetCollisionCollider(center, size);
	}

	bool CCollisionManager::Raycast(const Ray& ray, CColliderComponent*& hitObject, std::vector<CColliderComponent*>& ignores)
	{
		std::unordered_map<UINT32, CColliderComponent*> umIgnores;
		for (const auto obj : ignores)
		{
			umIgnores[obj->GetID()] = obj;
		}
	
		return CQuadTreeManager::Raycast(ray, hitObject, umIgnores);
	}

	bool CCollisionManager::Raycast(const Ray& ray, CColliderComponent*& hitObject, const std::vector<UINT>& checkLayer)
	{
		return CQuadTreeManager::Raycast(ray, hitObject, checkLayer);
	}

	void CCollisionManager::Initialize()
	{
		CQuadTreeManager::Initialize(Maths::Vector2(2048, 2048), 8, 2);
		m_vecCollider.resize(50);
	}

	void CCollisionManager::Release()
	{
		CQuadTreeManager::Release();
		delete[] m_bArryCollision;
		m_bArryCollision = nullptr;
	}

	void CCollisionManager::TickComponent()
	{
		//return;
		static float countTime = 0;
		static float checkTime = (float)1 / (float)80;
		static float timeCheck = 0;
		static INT fpsCheck = 0;
		
		timeCheck += TIME::RealDeltaTime();
		countTime += TIME::RealDeltaTime();

		if (countTime < checkTime)
		{	return;		}

		if (timeCheck >= 1.0f)
		{
			m_iCollTickComponentFPS = fpsCheck;
			fpsCheck = 0;
			timeCheck = 0;
		}
		else
		{
			fpsCheck += 1;
		}

		countTime = 0;

		ClearActor(); //삭제 예정 삭제
		CQuadTreeManager::Clear(); //쿼드 트리 초기화

		CScene* pScene = SCENE::GetCurrentScene();
		if (pScene == nullptr)				
		{	return;	}

		InsertCollision();
		CollisionCircuit();
	}

	void CCollisionManager::LastTickComponent()
	{	}

	void CCollisionManager::Render(HDC hdc)
	{
		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"CollFPS : %d", (int)(m_iCollTickComponentFPS));
		int len = (int)wcsnlen_s(str, 50);

		const Maths::Vector2 resolution = application.GetResolution();// - Maths::Vector2(100, 70);
		TextOut(hdc, ((int)resolution.x - 130), 20, str, len);
		//CQuadTreeManager::Render(hdc);
	}


	void CCollisionManager::CollisionStateUpdate(CColliderComponent* leftCollider, CColliderComponent* rightCollider)
	{
		CollisionID collId = { leftCollider->GetID() , rightCollider->GetID()};

		auto iter = m_unmapCollisions.find(collId.id);
		
		if (iter == m_unmapCollisions.end())
		{
			m_unmapCollisions.insert(std::make_pair(collId.id, false));
			iter = m_unmapCollisions.find(collId.id);
		}

		if (leftCollider->CheckCollision(rightCollider))
		{
			if (iter->second == false) //첫 충돌
			{
				leftCollider->OnCollisionEnter(rightCollider);
				rightCollider->OnCollisionEnter(leftCollider);
				iter->second = true;
			}
			else // 충돌 중
			{
				leftCollider->OnCollisionStay(rightCollider);
				rightCollider->OnCollisionStay(leftCollider);
			}
		}
		else
		{
			if (iter->second == true) //충돌 해제
			{
				leftCollider->OnCollisionExit(rightCollider);
				rightCollider->OnCollisionExit(leftCollider);
				iter->second = false;
			}
		}

	}

	void CCollisionManager::Clear()
	{
		CQuadTreeManager::Clear();
		m_unmapCollisions.clear();
		
		m_vecCollider.clear();
		m_vecCollider.shrink_to_fit();

		const UINT size = OBJECT::GetLayerSize();
		memset(m_bArryCollision, 0, sizeof(bool) * size * size);
	}


	void CCollisionManager::InsertCollision()
	{
		m_vecCollider.clear();

		for (UINT layer = 0; layer < OBJECT::GetLayerSize(); layer++)
		{
			const std::vector<CActor*>& vecDontDestroyObj	= SCENE::GetDontDestroyActor(layer);
			const std::vector<CActor*>& vecObj				= SCENE::GetActor(layer);

			InsertActor(vecDontDestroyObj);
			InsertActor(vecObj);
		}
	}

	void CCollisionManager::InsertActor(const std::vector<CActor*>& vecObjs)
	{
		for (const auto& pActor : vecObjs)
		{
			if (pActor->GetActive() &&
				pActor->GetReserveDelete() == false)
			{
				CColliderComponent* pCollider = pActor->GetComponent<CColliderComponent>();
				if (pCollider != nullptr)
				{
					CQuadTreeManager::Insert(pCollider);
					m_vecCollider.push_back(pCollider);
				}
			}
		}
	}

	void CCollisionManager::CollisionCircuit()
	{
		for (const auto& pCollider : m_vecCollider) //순회
		{
			const UINT leftLayer = (UINT)pCollider->GetOwner()->GetLayerType(); 

			const std::vector<CColliderComponent*>& possibleList = CQuadTreeManager::Query(pCollider); //해당 영역 오브젝트 가져오기

			for (const auto& possibleColl : possibleList)
			{
				if (pCollider != possibleColl)
				{
					const UINT rightLayer = (UINT)possibleColl->GetOwner()->GetLayerType();
					if (GetLayerState(leftLayer, rightLayer)) //서로 충돌 가능 레이어인지 비교
					{
						CollisionStateUpdate(pCollider, possibleColl);
					}
				}
			}
		}
	}

	bool CCollisionManager::GetLayerState(UINT left, UINT right)
	{
		const UINT size = OBJECT::GetLayerSize();
		return m_bArryCollision[(size * left) + right];
	}

}
