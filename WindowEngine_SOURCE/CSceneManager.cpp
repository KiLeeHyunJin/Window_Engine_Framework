#include "CSceneManager.h"
#include "CRenderManager.h"
#include "CCollisionManager.h"
#include "CObjectManager.h"
#include "CUIManager.h"

#include "Utils.h"

namespace Framework
{

	namespace Manager
	{
		CSceneManager* CSceneManager::s_instance = nullptr;
		//std::vector<CScene*>	CSceneManager::m_vecScenes = { nullptr };
		//CScene* CSceneManager::m_pCurrentScene = nullptr;
		////CScene*	CSceneManager::m_pDontDestroyScene						= nullptr;
		//UINT	CSceneManager::m_uiLayerSize = 0;
		//
		//CSceneManager::CSceneManager()
		//{
		//}

		CSceneManager::~CSceneManager()
		{
		}

		void CSceneManager::Initialize()
		{
		}

		void CSceneManager::Tick()
		{
			m_pCurrentScene->SceneTick();
			//m_pDontDestroyScene->SceneTick();

		}

		void CSceneManager::LastTick()
		{
			m_pCurrentScene->SceneLastTick();
			//m_pDontDestroyScene->SceneLastTick();
		}

		void CSceneManager::Render(HDC hDC)
		{
			m_pCurrentScene->Render(hDC);

			//m_pDontDestroyScene->Render(hDC);

			std::wstring str = m_pCurrentScene->GetName();
			Utils::DrawTxt(hDC, Maths::Vector2(0, 15), str);
		}

		void CSceneManager::Release()
		{
			for (auto& pScene : m_vecScenes)
			{
				if (pScene != nullptr)
				{
					pScene->OnExit();
					pScene->SceneRelease();
					delete pScene;
				}
			}
			m_vecScenes.clear();

			m_pCurrentScene = nullptr;
			//m_pDontDestroyScene = nullptr;
		}


		CScene* CSceneManager::LoadScene(const UINT idx)
		{
			CScene* pScene = FindScene(idx);
			if (pScene != nullptr)
			{
				if (m_pCurrentScene != nullptr)
				{
					m_pCurrentScene->OnExit();
					GET_SINGLE(COLLISION).Clear();
					GET_SINGLE(UI).Clear();
				}

				m_pCurrentScene = pScene;
				m_pCurrentScene->OnEnter();
				GET_SINGLE(OBJECT).Clear();
				return m_pCurrentScene;
			}
			return nullptr;
		}

		CScene* CSceneManager::FindScene(const UINT idx)
		{
			if (m_vecScenes.size() <= idx)
			{
				assert(true);
			}
			CScene* pScene = m_vecScenes[idx];
			//std::map<std::wstring, CScene*>::iterator iter = m_mapScene.find(name);
			/*if (iter != m_mapScene.end())
			{
				return iter->second;
			}*/
			return pScene;
		}

		void CSceneManager::InitSceneSize(UINT size)
		{
			if (m_vecScenes.size() >= size)
			{
				return;
			}

			if (m_vecScenes.size() < size)
			{
				m_vecScenes.resize(size);
				//m_vecScenes[m_vecScenes.size() - 1] = m_pDontDestroyScene;
			}
			//GET_SINGLE(COLLISION).InitCollisionLayer();
		}
	}

	
}