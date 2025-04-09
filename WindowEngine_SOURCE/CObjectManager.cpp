#include "CObjectManager.h"
#include "CActor.h"
#include "CCollisionManager.h"
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
			AddActorID(pActor);
			AddInLayer(pActor);
		}

		void CObjectManager::AddActorID(CActor* pActor)
		{
			const UINT32 id = pActor->GetID();

			auto iter = m_unObjects.find(id);
			if (iter == m_unObjects.end())			//존재 하지 않는 아이디
			{
				m_unObjects.insert(std::make_pair(id, pActor));
			}
			else
			{
				if (iter->second == nullptr)		//소멸된 아이디
				{
					iter->second = pActor;
				}
				else//존재하는 아이디
				{
					assert(true);
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
				layer->Destroy();
			}
			for (auto layer : m_vecDontDestoryLayer)
			{
				layer->Destroy();
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
		void CObjectManager::Render(HDC hdc)
		{
			for (UINT i = 0; i < m_uiLayerSize; i++)
			{
				m_vecLayer[i]->Render(hdc);
				m_vecDontDestoryLayer[i]->Render(hdc);
			}
		}
	}
	
}
