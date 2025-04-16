#include "CCollisionManager.h"
#include "CSceneManager.h"
#include "CQuadTreeManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"

#include "CLayer.h"
#include "CActor.h"

#include "CTransformComponent.h"
#include "CColliderComponent.h"
#include "CObjectManager.h"
#include "CApplication.h"
//#include 
//extern Framework::CApplication application;

namespace Framework
{

	namespace Manager
	{
		CCollisionManager* CCollisionManager::s_instance = nullptr;


		CCollisionManager::~CCollisionManager() //사용안함
		{
		}

		void CCollisionManager::InitCollisionLayer()
		{
			if (m_bArryCollision != nullptr)
			{
				return;
			}

			const UINT size = GET_SINGLE(OBJECT).GetLayerSize();
			if (size == 0)
			{
				return;
			}
			const UINT fullSize = size * size;
			m_bArryCollision = new bool[fullSize];
			for (UINT i = 0; i < fullSize; i++)
			{
				m_bArryCollision[i] = false;
 			}
		}

		void CCollisionManager::SetCollisionLayerState(UINT left, UINT right, bool enable)
		{
			const UINT size = GET_SINGLE(OBJECT).GetLayerSize();
			if (left > size || right > size ||
				m_bArryCollision == nullptr)
			{
				int a = 5;
				assert(1);
				return;
			}

			UINT row, col;
			if (left < right)
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
			const Maths::Vector2 center = (rect.max + rect.min) * 0.5f;
			const Maths::Vector2 size = rect.max - rect.min;

			return GetCollisionCollider(center, size);
		}

		bool CCollisionManager::Raycast(const Ray& ray, CColliderComponent*& hitObject, std::vector<CColliderComponent*>& ignores)
		{
			std::unordered_map<UINT32, CColliderComponent*> umIgnores;
			for (const auto obj : ignores)
			{
				umIgnores[obj->GetColliderID()] = obj;
			}

			return CQuadTreeManager::Raycast(ray, hitObject, umIgnores);
		}

		bool CCollisionManager::Raycast(const Ray& ray, CColliderComponent*& hitObject, const std::vector<UINT>& checkLayer)
		{
			return CQuadTreeManager::Raycast(ray, hitObject, checkLayer);
		}

		void CCollisionManager::Initialize()
		{
			CQuadTreeManager::Initialize(Maths::Vector2(8192, 8192), 8, 1.2f);
			m_vecCollider.resize(50);

			collisionsA.reserve(200);
			collisionsB.reserve(200);

			this->curr = &collisionsA;
			this->prev = &collisionsB;
		}

		void CCollisionManager::Release()
		{
			Clear();
			CQuadTreeManager::Release();
			delete[] m_bArryCollision;
			m_bArryCollision = nullptr;
		}

		void CCollisionManager::Tick()
		{
			//return;
			if(false)
			{
				static float countTime = 0;
				static float checkTime = (float)1 / (float)80;
				static float timeCheck = 0;
				static UINT fpsCheck = 0;

				timeCheck += GET_SINGLE(TIME).RealDeltaTime();
				countTime += GET_SINGLE(TIME).RealDeltaTime();

				if (countTime < checkTime)
				{
					return;
				}
				else
				{
					countTime = 0;

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
				}
			}


			//충돌 검사를 위한 이중 버퍼
			std::swap(curr, prev);
			curr->clear();

			GET_SINGLE(OBJECT).Destroy();			//삭제 예정 삭제
			CQuadTreeManager::Clear();	//쿼드 트리 초기화

			InsertCollision();
			CollisionCircuit();
		}

		void CCollisionManager::LastTick()
		{
		}

		void CCollisionManager::Render(HDC hdc) const
		{
			CQuadTreeManager::Render(hdc);

			wchar_t str[50] = L"";
			swprintf_s(str, 50, L"충돌횟수 : %d", (int)(m_iCollTickComponentFPS));
			int len = (int)wcsnlen_s(str, 50);

			const Maths::Vector2 resolution = GET_SINGLE(RENDER).GetResolution();// - Maths::Vector2(100, 70);
			TextOut(hdc, ((int)resolution.x - 130), 20, str, len);
		}


		void CCollisionManager::CollisionStateUpdate(CColliderComponent* leftCollider, CColliderComponent* rightCollider)
		{
			UINT32 leftID = leftCollider->GetColliderID();
			UINT32 rightID = rightCollider->GetColliderID();

			if (leftID > rightID)
			{
				std::swap(leftID, rightID);
			}

			const CollisionID collId = { leftID, rightID };
			if (curr->find(collId.id) != curr->end()) //이미 충돌검사가 진행되었었다면 종료
			{		return;		}

			bool prevState;
			auto prevIter = prev->find(collId.id);
			if (prevIter != prev->end())
			{
				prevState = prevIter->second;
			}
			else
			{
				prevState = false;
			}

			const bool state = leftCollider->CheckCollision(rightCollider);
			if (state)
			{
				if (prevState == false)
				{
					leftCollider->OnCollisionEnter(rightCollider);
					rightCollider->OnCollisionEnter(leftCollider);
				}
				else
				{
					leftCollider->OnCollisionStay(rightCollider);
					rightCollider->OnCollisionStay(leftCollider);
				}
			}
			else
			{
				if (prevState)
				{
					leftCollider->OnCollisionExit(rightCollider);
					rightCollider->OnCollisionExit(leftCollider);
				}
			}
			curr->insert(std::make_pair(collId.id, state));
		}

		void CCollisionManager::Clear()
		{
			CQuadTreeManager::Clear();
			prev->clear();
			curr->clear();

			m_vecCollider.clear();
			m_vecCollider.shrink_to_fit();

			const UINT size = GET_SINGLE(OBJECT).GetLayerSize();
			memset(m_bArryCollision, 0, sizeof(bool) * size * size);
		}


		void CCollisionManager::InsertCollision()
		{
			m_vecCollider.clear();

			for (UINT layer = 0; layer < GET_SINGLE(OBJECT).GetLayerSize(); layer++)
			{
				const std::vector<CActor*>& vecDontDestroyObj = GET_SINGLE(OBJECT).GetDontDestroyActors(layer);
				const std::vector<CActor*>& vecObj = GET_SINGLE(OBJECT).GetActors(layer);

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
				const UINT32 colliderID = pCollider->GetColliderID();
				const std::vector<CColliderComponent*>& possibleList = CQuadTreeManager::Query(pCollider); //해당 영역 오브젝트 가져오기

				for (const auto& possibleColl : possibleList)
				{
					const UINT32 possibleColliderID = possibleColl->GetColliderID();
					if (colliderID != possibleColliderID)
					{
						const UINT rightLayer = (UINT)possibleColl->GetOwner()->GetLayerType();
						const bool state = GetLayerState(leftLayer, rightLayer);
						if (state) //서로 충돌 가능 레이어인지 비교
						{
							CollisionStateUpdate(pCollider, possibleColl);
						}
					}
				}
			}
		}

		bool CCollisionManager::GetLayerState(UINT left, UINT right)
		{
			const UINT size = GET_SINGLE(OBJECT).GetLayerSize();
			UINT row, col;
			if (left < right)
			{
				row = left;
				col = right;
			}
			else
			{
				col = left;
				row = right;
			}
			const bool state = m_bArryCollision[(row * size) + col];
			return state;
		}

	}

}
