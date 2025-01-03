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
		for (const std::pair<std::wstring, CScene*>& scenePair : m_mapScene)
		{
			delete scenePair.second;
		}
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
		for (const std::pair<std::wstring, CScene*>& scenePair : m_mapScene)
		{
			scenePair.second->SceneRelease();
		}
	}
}