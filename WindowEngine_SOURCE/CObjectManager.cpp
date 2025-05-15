#include "CObjectManager.h"
#include "CActor.h"
#include "CCollisionManager.h"
#include "CRenderManager.h"
#include "CTimeManager.h"

namespace Framework
{
	namespace Manager
	{
		CObjectManager* CObjectManager::s_instance = nullptr;

		//UINT CObjectManager::m_uiLayerSize = 0;
		//std::unordered_map<UINT32, CActor*> CObjectManager::m_unObjects = {};
		//
		//std::vector<CLayer*> CObjectManager::m_vecLayer = {};
		//std::vector<CLayer*> CObjectManager::m_vecDontDestoryLayer = {};

		CObjectManager::~CObjectManager()
		{
		}

		bool CObjectManager::ActorCheck(CActor* pActor)
		{
			const UINT32 currentId = pActor->GetID();
			if (currentId != 0)
			{
				auto iter = m_unObjects.find(currentId);
				if (iter != m_unObjects.end())
				{
					CActor* target = iter->second;
					if (target == pActor)
					{
						return false;
					}
				}
			}
			return true;
		}

		void CObjectManager::GrantID(CActor* pActor)
		{
			UINT32 id = GET_SINGLE(TIME).GetRandom();

			auto iter = m_unObjects.find(id);
			if (iter != m_unObjects.end())				//사용 흔적이 있는 아이디
			{
				if (iter->second == nullptr)			//소멸된 아이디
				{
					m_unObjects.erase(iter);
				}
				else
				{
					while (true)								//사용안하는 ID가 나올때까지 탐색
					{
						id = GET_SINGLE(TIME).GetRandom();
						auto iter = m_unObjects.find(id);
						if (iter == m_unObjects.end())			//사용하지 않는 아이디
						{
							break;
						}
						else
						{
							if (iter->second == nullptr)		//소멸된 아이디
							{
								m_unObjects.erase(iter);
								break;
							}
						}
					}
				}
				
			}
			m_unObjects.insert(std::make_pair(id, pActor));		//정보 기록

			pActor->SetID(id);									//ID부여
			pActor->Initialize();								//초기화 진행

			return;
		}

		void CObjectManager::EnterLayer(CActor* pActor)
		{
			AddInLayer(pActor);
			pActor->BeginPlay();
		}

		void CObjectManager::CreateID(CActor* pActor)
		{
			if (ActorCheck(pActor) == false)
			{	return ;	}
			GrantID(pActor);
		}

		void CObjectManager::DeleteID(CActor* pActor)
		{
			const UINT id = pActor->GetID();
			auto iter = m_unObjects.find(id);
			if (iter != m_unObjects.end())
			{
				m_unObjects.erase(iter);
			}
		}

		void CObjectManager::AddInLayer(CActor* pActor)
		{
			const bool dontDestroy = pActor->GetDontDestroy();
			const UINT layer = pActor->GetLayerType();

			auto& vecLayer = dontDestroy ? m_vecDontDestoryLayer : m_vecLayer;
			vecLayer[layer]->AddActor(pActor);
		}

		bool CObjectManager::EraseInLayer(CActor* pActor)
		{
			const bool dontDestroy = pActor->GetDontDestroy();
			const UINT layer = pActor->GetLayerType();

			auto& vecLayer = dontDestroy ? m_vecDontDestoryLayer : m_vecLayer;
			const bool result = vecLayer[layer]->EraseInIndex(pActor);
			return result;
		}

		void CObjectManager::Clear(bool allClear)
		{
			for (auto layer : m_vecLayer)
			{
				layer->Clear();
			}

			if (allClear == false) { return; }

			for (auto layer : m_vecDontDestoryLayer)
			{
				layer->Clear();
			}
		}

		void CObjectManager::Destroy()
		{
			//데이터 정리
			for (auto layer : m_vecLayer)
			{
				layer->ReleaseActor();
			}
			for (auto layer : m_vecDontDestoryLayer)
			{
				layer->ReleaseActor();
			}
			//할당 해제
			for (auto layer : m_vecLayer)
			{
				layer->DeleteActor();
			}
			for (auto layer : m_vecDontDestoryLayer)
			{
				layer->DeleteActor();
			}
		}

		void CObjectManager::RemoveActor(CActor* pActor)
		{
			const UINT parentID = pActor->GetParentID();
			CActor* pParent = parentID == 0 ? nullptr : GetActor(parentID); //부모 아이디를 통해 부모를 찾기
			if (pParent != nullptr)
			{
				pParent->RemoveChild(pActor->GetID());
			}
		}

		void CObjectManager::InitLayerSize(UINT layerSize)
		{
			if (m_uiLayerSize != 0)	//데이터가 설정되었을 경우 변경 불가
			{
				return;
			}

			m_uiLayerSize = layerSize;

			m_vecDontDestoryLayer.resize(m_uiLayerSize);
			m_vecLayer.resize(m_uiLayerSize);

			for (UINT i = 0; i < m_uiLayerSize; i++)
			{
				m_vecDontDestoryLayer[i] = new CLayer(i);
				m_vecLayer[i] = new CLayer(i);
			}

			GET_SINGLE(COLLISION).InitCollisionLayer();
		}

		void CObjectManager::Initialize()
		{
		}

		void CObjectManager::Release()
		{
			//액터 데이터 정리
			for (auto& layer : m_vecLayer)
			{
				layer->Release();
			}
			for (auto& layer : m_vecDontDestoryLayer)
			{
				layer->Release();
			}
			//액터 & 레이어 메모리 해제
			for (auto& layer : m_vecLayer)
			{
				layer->Delete();
				delete layer;
			}
			for (auto& layer : m_vecDontDestoryLayer)
			{
				layer->Delete();
				delete layer;
			}
			m_unObjects.clear();
			m_vecLayer.clear();
			m_vecDontDestoryLayer.clear();
		}

		void CObjectManager::Tick()
		{
			for (UINT i = 0; i < m_uiLayerSize; i++)
			{
				m_vecLayer[i]->Tick();
				m_vecDontDestoryLayer[i]->Tick();
			}
		}
		void CObjectManager::LastTick()
		{
			for (UINT i = 0; i < m_uiLayerSize; i++)
			{
				m_vecLayer[i]->LastTick();
				m_vecDontDestoryLayer[i]->LastTick();
			}
		}
		void CObjectManager::FixedTick()
		{
			for (UINT i = 0; i < m_uiLayerSize; i++)
			{
				m_vecLayer[i]->FixedTick();
				m_vecDontDestoryLayer[i]->FixedTick();
			}
		}

		void CObjectManager::Render(HDC hdc)
		{
			for (UINT i = 0; i < m_uiLayerSize; i++)
			{
				m_vecLayer[i]->Render(hdc);
				m_vecDontDestoryLayer[i]->Render(hdc);
			}

			wchar_t str[50] = L"";
			swprintf_s(str, 50, L"오브젝트 개수 : %d", (int)(m_unObjects.size()));
			int len = (int)wcsnlen_s(str, 50);

			const Maths::Vector2 resolution = GET_SINGLE(RENDER).GetResolution();// - Maths::Vector2(100, 70);
			TextOut(hdc, ((int)resolution.x - 150), 40, str, len);

			wchar_t str2[50] = L"";
			swprintf_s(str2, 50, L"FPS : %d", (GET_SINGLE(TIME).FPS));
			int len2 = (int)wcsnlen_s(str2, 50);

			TextOut(hdc, ((int)resolution.x - 150), 60, str2, len2);
		}
	}
	
}
