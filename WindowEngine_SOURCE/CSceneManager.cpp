#include "CSceneManager.h"
#include "CScene.h"

namespace Framework
{
	map<wstring,CScene*>	CSceneManager::m_mapScene		= {};
	CScene*			CSceneManager::m_pCurrentScene	= nullptr;


	CSceneManager::CSceneManager()
	{
	}
	CSceneManager::~CSceneManager()
	{
		for (const pair<wstring, CScene*>& scenePair : m_mapScene)
		{
			delete scenePair.second;
		}
	}

	void CSceneManager::Initialize()
	{
		m_pCurrentScene->Initialize();
	}

	void CSceneManager::Tick()
	{
		m_pCurrentScene->Tick();
	}

	void CSceneManager::LastTick()
	{
		m_pCurrentScene->LastTick();
	}

	void CSceneManager::Render(HDC hDC)
	{
		m_pCurrentScene->Render(hDC);
	}

	void CSceneManager::Release()
	{
		for (const pair<wstring, CScene*>& scenePair : m_mapScene)
		{
			scenePair.second->Release();
		}
	}
}