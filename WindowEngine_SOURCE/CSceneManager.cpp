#include "CSceneManager.h"
#include "CScene.h"
#include "CDontDestroyOnLoad.h"

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
		m_pDontDestroyScene = FindScene(L"DontDestroyOnLoad");
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
		m_pCurrentScene->SceneRender(hDC);
		m_pDontDestroyScene->SceneRender(hDC);
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

	CScene* CSceneManager::LoadScene(const std::wstring& name)
	{
		CScene* pScene = FindScene(name);
		if (pScene != nullptr)
		{
			if (m_pCurrentScene != nullptr)
			{
				m_pCurrentScene->OnExit();
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