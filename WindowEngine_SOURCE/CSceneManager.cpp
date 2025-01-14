#include "CSceneManager.h"
#include "CScene.h"

namespace Framework
{
	std::map<std::wstring,CScene*>	CSceneManager::m_mapScene		= {};
	CScene*			CSceneManager::m_pCurrentScene	= nullptr;


	CSceneManager::CSceneManager()
	{
	}
	CSceneManager::~CSceneManager()
	{
	}

	void CSceneManager::Initialize()
	{
		m_pCurrentScene->SceneInitialize();
	}

	void CSceneManager::Tick()
	{
		m_pCurrentScene->SceneTick();
	}

	void CSceneManager::LastTick()
	{
		m_pCurrentScene->SceneLastTick();
	}

	void CSceneManager::Render(HDC hDC)
	{
		m_pCurrentScene->SceneRender(hDC);
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
	}

	CScene* CSceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, CScene*>::iterator iter = m_mapScene.find(name);
		if (iter != m_mapScene.end())
		{
			if (m_pCurrentScene != nullptr)
			{
				m_pCurrentScene->OnExit();
			}
			m_pCurrentScene = iter->second;
			m_pCurrentScene->OnEnter();
			return m_pCurrentScene;
		}
		return nullptr;
	}
}