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

		void CObjectManager::AddActor(CActor* pActor)
		{
			pActor->Initialize();
			AddActorID(pActor);
			AddInLayer(pActor);
			pActor->BeginPlay();
		}

		void CObjectManager::AddActorID(CActor* pActor)
		{
			const UINT32 id = GET_SINGLE(TIME).GetRandom();
			auto iter = m_unObjects.find(id);
			if (iter == m_unObjects.end())			//존재 하지 않는 아이디
			{
				m_unObjects.insert(std::make_pair(id, pActor));
				pActor->SetID(id);
				return;
			}

			UINT32 _id = iter->first;
			CActor* target = iter->second;
			if (target == nullptr)		//소멸된 아이디
			{
				iter->second = pActor;
				return;
			}
			
			if (target == pActor)
			{	return;		}

			assert(false);
			while (true)
			{
				const UINT32 newID = GET_SINGLE(TIME).GetRandom();
				auto iter = m_unObjects.find(newID);
				if (iter == m_unObjects.end())			//존재 하지 않는 아이디
				{
					pActor->SetID(newID);
					m_unObjects.insert(std::make_pair(newID, pActor));
					break;
				}
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
			for (auto layer : m_vecLayer)
			{
				layer->DestroyActor();
			}
			for (auto layer : m_vecDontDestoryLayer)
			{
				layer->DestroyActor();
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
			for (auto& layer : m_vecLayer)
			{
				layer->Release();
				delete layer;
			}
			m_vecLayer.clear();
			for (auto& layer : m_vecDontDestoryLayer)
			{
				layer->Release();
				delete layer;
			}
			m_vecDontDestoryLayer.clear();
			m_unObjects.clear();
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
