#include "CSceneManager.h"
#include "CScene.h"
#include "CDontDestroyOnLoad.h"

#include "CRenderManager.h"
#include "CCollisionManager.h"
#include "CUIManager.h"
//#include "CEventManager.h"

namespace Framework
{
	std::vector<CScene*>	CSceneManager::m_vecScenes				= {nullptr};
	CScene* CSceneManager::m_pCurrentScene							= nullptr;
	CScene*	CSceneManager::m_pDontDestroyScene						= nullptr;
	//CScene* CSceneManager::m_pChangeScene							= nullptr;

	CSceneManager::CSceneManager()
	{
	}

	CSceneManager::~CSceneManager()
	{
	}

	void CSceneManager::Initialize()
	{
		CDontDestroyOnLoad* pDontDestroyScene = new CDontDestroyOnLoad;
		m_pDontDestroyScene = static_cast<CScene*>(pDontDestroyScene);
		m_pDontDestroyScene->SetName(L"DontDestroyScene");
		m_pDontDestroyScene->SceneInitialize();

		//if (m_pCurrentScene != nullptr)
		//{
		//	m_pCurrentScene->SceneInitialize();
		//}
	}

	void CSceneManager::Tick()
	{
		Destroy();

		m_pCurrentScene->SceneTick();
		m_pDontDestroyScene->SceneTick();
	}

	void CSceneManager::LastTick()
	{
		m_pCurrentScene->SceneLastTick();
		m_pDontDestroyScene->SceneLastTick();
	}

	void CSceneManager::Destroy()
	{
		m_pCurrentScene->SceneDestroy();
		m_pDontDestroyScene->SceneDestroy();
	}

	void CSceneManager::Render(HDC hDC)
	{
		for (UINT i = (UINT)Enums::eLayerType::None; i < (UINT)Enums::eLayerType::Size; i++)
		{
			const CLayer* pCurrentLayer = m_pCurrentScene->GetLayer((Enums::eLayerType)i);
			const CLayer* pDontDestroyLayer = m_pDontDestroyScene->GetLayer((Enums::eLayerType)i);

			pCurrentLayer->Render(hDC);
			pDontDestroyLayer->Render(hDC);
		}
		m_pCurrentScene->SceneRender(hDC);
		
		std::wstring str = m_pCurrentScene->GetName();
		RENDER::DrawWText(hDC, 0, 15, str);
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
		m_pDontDestroyScene = nullptr;
	}

	//std::vector<CGameObject*> CSceneManager::GetGameObject(Enums::eLayerType layer)
	//{
	//	std::vector<CGameObject*> gameObjects = m_pCurrentScene->GetLayer(layer)->GetGameObject();
	//	const std::vector<CGameObject*>& dontDestroyGameObjects = m_pDontDestroyScene->GetLayer(layer)->GetGameObject();

	//	// 추가 공간을 미리 예약하여 재할당을 최소화
	//	const INT sceneSize = (INT)gameObjects.size();
	//	const INT dontDestroySize = (INT)dontDestroyGameObjects.size();
	//	gameObjects.reserve(sceneSize + dontDestroySize);

	//	// dontDestroyGameObjects의 모든 요소를 gameObjects에 추가
	//	gameObjects.insert(gameObjects.end(), dontDestroyGameObjects.begin(), dontDestroyGameObjects.end());
	//	return gameObjects;
	//}


	const std::vector<CGameObject*>& CSceneManager::GetDontDestroyGameObject(Enums::eLayerType layer)
	{
		return m_pDontDestroyScene->GetLayer(layer)->GetGameObject();
	}

	const std::vector<CGameObject*>& CSceneManager::GetGameObject(Enums::eLayerType layer)
	{
		return  m_pCurrentScene->GetLayer(layer)->GetGameObject();
	}

	CScene* CSceneManager::LoadScene(const UINT idx)
	{
		CScene* pScene = FindScene(idx);
		if (pScene != nullptr)
		{
			if (m_pCurrentScene != nullptr)
			{
				m_pCurrentScene->OnExit();
				CCollisionManager::Clear();
				CUIManager::Clear();
			}
			m_pCurrentScene = pScene;
			m_pCurrentScene->OnEnter();
			return m_pCurrentScene;
		}
		return nullptr;
	}

	CScene* CSceneManager::FindScene(const UINT idx)
	{
		CScene* pScene = m_vecScenes[idx];
		//std::map<std::wstring, CScene*>::iterator iter = m_mapScene.find(name);
		/*if (iter != m_mapScene.end())
		{
			return iter->second;
		}*/
		return pScene;
	}
}