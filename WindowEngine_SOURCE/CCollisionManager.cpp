#include "CCollisionManager.h"
#include "CSceneManager.h"
#include "CQuadTreeManager.h"
#include "CTimeManager.h"

#include "CLayer.h"
#include "CGameObject.h"

#include "CTransformComponent.h"
#include "CColliderComponent.h"
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
	INT CCollisionManager::m_iCollTickFPS = 0;

	CCollisionManager::CCollisionManager()	//사용안함
	{	}
	CCollisionManager::~CCollisionManager() //사용안함
	{	}

	void CCollisionManager::InitCollisionLayer()
	{
		if (m_bArryCollision != nullptr)
		{	return;		}

		const UINT size = SCENE::GetLayerSize();
		const UINT fullSize = size * size;
		m_bArryCollision = new bool [fullSize];
		memset(m_bArryCollision, 0, sizeof(bool) * fullSize);

	}

	void CCollisionManager::ClearGameObject()
	{
		SCENE::Destroy();
	}

	void CCollisionManager::SetCollisionLayerState(UINT left, UINT right, bool enable)
	{
		const UINT size = SCENE::GetLayerSize();
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

	void CCollisionManager::Tick()
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
			m_iCollTickFPS = fpsCheck;
			fpsCheck = 0;
			timeCheck = 0;
		}
		else
		{
			fpsCheck += 1;
		}

		countTime = 0;

		ClearGameObject(); //삭제 예정 삭제
		CQuadTreeManager::Clear(); //쿼드 트리 초기화

		CScene* pScene = SCENE::GetCurrentScene();
		if (pScene == nullptr)				
		{	return;	}

		//clock_t start, finish;
		//start = clock();

		InsertCollision();
		CollisionCircuit();
		
		//finish = clock();
		//duration = (double)(finish - start) / CLOCKS_PER_SEC;
	}

	void CCollisionManager::LastTick()
	{	}

	void CCollisionManager::Render(HDC hdc)
	{
		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"CollFPS : %d", (int)(m_iCollTickFPS));
		int len = (int)wcsnlen_s(str, 50);

		const Maths::Vector2 resolution = application.GetResolution();// - Maths::Vector2(100, 70);
		TextOut(hdc, ((int)resolution.x - 130), 20, str, len);
		//CQuadTreeManager::Render(hdc);
		//
	}

#pragma region NoUsed
	/*void CCollisionManager::CollisionCheck(CScene* pScene, Enums::eLayerType left, Enums::eLayerType right)
	{
		const std::vector<CGameObject*>& lefts = CSceneManager::GetGameObject(left);
		const std::vector<CGameObject*>& rights = CSceneManager::GetGameObject(right);
		const std::vector<CGameObject*>& dontDestroyLefts = CSceneManager::GetDontDestroyGameObject(left);
		const std::vector<CGameObject*>& dontDestroyrights = CSceneManager::GetDontDestroyGameObject(right);

		CollisionCheck(lefts, rights);
		CollisionCheck(dontDestroyLefts, rights);

		CollisionCheck(dontDestroyLefts, dontDestroyrights);
	}*/

	/*void CCollisionManager::CollisionCheck(const std::vector<CGameObject*>& lefts, const std::vector<CGameObject*>& rights)
	{
		for (CGameObject* leftObj : lefts)
		{
			if (leftObj == nullptr)
			{
				continue;
			}
			if (leftObj->GetActive() == false)
			{
				continue;
			}
			CColliderComponent* leftCollider = leftObj->GetComponent<CColliderComponent>();
			if (leftCollider == nullptr)
			{
				continue;
			}

			for (CGameObject* rightObj : rights)
			{
				if (leftObj == rightObj)
				{
					continue;
				}
				if (rightObj == nullptr)
				{
					continue;
				}
				if (rightObj->GetActive() == false)
				{
					continue;
				}
				CColliderComponent* rightCollider = rightObj->GetComponent<CColliderComponent>();
				if (rightCollider == nullptr)
				{
					continue;
				}
				CollisionStateUpdate(leftCollider, rightCollider);
			}
		}
	}
*/
#pragma endregion

	void CCollisionManager::CollisionStateUpdate(CColliderComponent* leftCollider, CColliderComponent* rightCollider)
	{
		CollisionID collId = { leftCollider->GetID() , rightCollider->GetID()};

		auto iter = m_unmapCollisions.find(collId.id);
		
		if (iter == m_unmapCollisions.end())
		{
			m_unmapCollisions.insert(std::make_pair(collId.id, false));
			iter = m_unmapCollisions.find(collId.id);
		}

		if (Intersect(leftCollider, rightCollider))
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

		const UINT size = SCENE::GetLayerSize();
		memset(m_bArryCollision, 0, sizeof(bool) * size * size);
	}



	const bool CCollisionManager::Intersect(const CColliderComponent* left, const CColliderComponent* right)
	{
		const CColliderComponent::eColliderType leftType  = left->GetColliderType();
		const CColliderComponent::eColliderType rightType = right->GetColliderType();

		if ( leftType == CColliderComponent::eColliderType::Box &&
			rightType == CColliderComponent::eColliderType::Box)
		{
			return BoxCollisionStateUpdate(left, right);
		}
		else if 
			(leftType == CColliderComponent::eColliderType::Circle &&
			rightType == CColliderComponent::eColliderType::Circle)
		{
			return CircleCollisionStateUpdate(left, right);
		}
		return false;
	}

	void CCollisionManager::InsertCollision()
	{
		m_vecCollider.clear();

		for (UINT layer = 0; layer < SCENE::GetLayerSize(); layer++)
		{
			const std::vector<CGameObject*>& vecDontDestroyObj 
				= SCENE::GetDontDestroyGameObject(layer);

			const std::vector<CGameObject*>& vecObj 
				= SCENE::GetGameObject(layer);

			for (auto& pGameObject : vecObj)
			{
				if (pGameObject->GetActive() && 
					pGameObject->GetReserveDelete() == false)
				{
					CColliderComponent* pCollider = pGameObject->GetComponent<CColliderComponent>();
					InsertGameObject(pCollider);
				}
			}
			for (const auto& pGameObject : vecDontDestroyObj)
			{
				if (pGameObject->GetActive() &&
					pGameObject->GetReserveDelete() == false)
				{
					CColliderComponent* pCollider = pGameObject->GetComponent<CColliderComponent>();
					InsertGameObject(pCollider);
				}
			}
		}
	}

	void CCollisionManager::InsertGameObject(CColliderComponent* pCollider)
	{
		if (pCollider != nullptr)
		{
			CQuadTreeManager::Insert(pCollider);
			m_vecCollider.push_back(pCollider);
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
					if (GetLayerState(leftLayer, rightLayer))
					{
						CollisionStateUpdate(pCollider, possibleColl);
					}
				}
			}
		}
	}


	bool CCollisionManager::BoxCollisionStateUpdate(const CColliderComponent* left,const CColliderComponent* right)
	{
		const CTransformComponent* leftTr = left->GetOwner()->GetTransformComponent();
		const CTransformComponent* rightTr = right->GetOwner()->GetTransformComponent();

		const Maths::Vector2 leftPos = leftTr->GetPos() + left->GetOffset();
		const Maths::Vector2 rightPos = rightTr->GetPos() + right->GetOffset();

		const Maths::Vector2 leftSize = left->GetSize();
		const Maths::Vector2 rightSize = right->GetSize();

		if (Maths::Abs(leftPos.x - rightPos.x) < Maths::Abs((leftSize.x + rightSize.x) * 0.5f) &&
			Maths::Abs(leftPos.y - rightPos.y) < Maths::Abs((leftSize.y + rightSize.y) * 0.5f))
		{
			return true;
		}
		return false;
	}

	bool CCollisionManager::CircleCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right)
	{
		const CTransformComponent* leftTr = left->GetOwner()->GetComponent<CTransformComponent>();
		const CTransformComponent* rightTr = right->GetOwner()->GetComponent<CTransformComponent>();

		Maths::Vector2 leftPos = leftTr->GetPos() + left->GetOffset();
		Maths::Vector2 rightPos = rightTr->GetPos() + right->GetOffset();

		Maths::Vector2 leftSize = left->GetSize() * 100;
		Maths::Vector2 rightSize = right->GetSize() * 100;

		const Maths::Vector2 leftCirclePos	= leftPos  + (leftSize * 0.5f);
		const Maths::Vector2 rightCirclePos = rightPos + (rightSize * 0.5f);

		const float lenght = (Maths::Vector2(leftCirclePos.x + rightCirclePos.x, leftCirclePos.y + rightCirclePos.y)).Length();

		if (lenght <= (leftSize.x + rightSize.x) * 0.5f)
		{
			return true;
		}
		return false;
	}

	bool CCollisionManager::GetLayerState(UINT left, UINT right)
	{

		const UINT size = SCENE::GetLayerSize();
		return m_bArryCollision[(size * left) + right];
	}

}
