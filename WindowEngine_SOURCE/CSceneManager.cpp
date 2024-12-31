#include "CSceneManager.h"
#include "CScene.h"

namespace Framework
{
	vector<CScene*>	CSceneManager::m_vecScene		= {};
	CScene*			CSceneManager::m_pCurrentScene	= nullptr;


	CSceneManager::CSceneManager()
	{
	}
	CSceneManager::~CSceneManager()
	{
		for (CScene* scene : m_vecScene)
		{
			delete scene;
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
		m_pCurrentScene->Release();
	}
}