#include "CSceneManager.h"
#include "CScene.h"
#include "CDontDestroyOnLoad.h"
#include "CCollisionManager.h"

namespace Framework
{
	std::map<std::wstring,CScene*>	CSceneManager::m_mapScene		= {};
	CScene* CSceneManager::m_pCurrentScene = nullptr;
	CScene*	CSceneManager::m_pDontDestroyScene = nullptr;


	CSceneManager::CSceneManager()
	{

	}
	CSceneManager::~CSceneManager()
	{
	}

	void CSceneManager::Initialize()
	{
		m_pDontDestroyScene = CreateScene<CDontDestroyOnLoad>(L"DontDestroyOnLoad");
		m_pCurrentScene->SceneInitialize();
	}

	void CSceneManager::Tick()
	{
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
	}

	void CSceneManager::Release()
	{
		for (auto& scenePair : m_mapScene)
		{
			//scenePair.second->OnExit();
			scenePair.second->SceneRelease();
			delete scenePair.second;
		}
		m_mapScene.clear();

		m_pCurrentScene = nullptr;
		m_pDontDestroyScene = nullptr;
	}

	std::vector<CGameObject*> CSceneManager::GetGameObject(Enums::eLayerType layer)
	{
		std::vector<CGameObject*> gameObjects = m_pCurrentScene->GetLayer(layer)->GetGameObject();
		const std::vector<CGameObject*>& dontDestroyGameObjects = m_pDontDestroyScene->GetLayer(layer)->GetGameObject();

		// 추가 공간을 미리 예약하여 재할당을 최소화
		const INT sceneSize = (INT)gameObjects.size();
		const INT dontDestroySize = (INT)dontDestroyGameObjects.size();
		gameObjects.reserve(sceneSize + dontDestroySize);

		// dontDestroyGameObjects의 모든 요소를 gameObjects에 추가
		gameObjects.insert(gameObjects.end(), dontDestroyGameObjects.begin(), dontDestroyGameObjects.end());
		return gameObjects;
	}

	CScene* CSceneManager::LoadScene(const std::wstring& name)
	{
		CScene* pScene = FindScene(name);
		if (pScene != nullptr)
		{
			if (m_pCurrentScene != nullptr)
			{
				m_pCurrentScene->OnExit();
				CCollisionManager::Clear();
			}
			m_pCurrentScene = pScene;
			m_pCurrentScene->OnEnter();
			return m_pCurrentScene;
		}
		return nullptr;
	}

	CScene* CSceneManager::FindScene(const std::wstring& name)
	{
		std::map<std::wstring, CScene*>::iterator iter = m_mapScene.find(name);
		if (iter != m_mapScene.end())
		{
			return iter->second;
		}
		return nullptr;
	}
}