#include "CScene.h"
#include "CGameObject.h"

namespace Framework
{
	CScene::CScene()
	{
	}

	CScene::~CScene()
	{
	}
	void CScene::SceneInitialize()
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->Initialize();
		}
		Initialize();
	}
	void CScene::SceneRelease()
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->Release();
		}
		Release();
	}
	void CScene::SceneTick()
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->Tick();
		}
		Tick();
	}
	void CScene::SceneLastTick()
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->LastTick();
		}
		LastTick();
	}
	void CScene::SceneRender(HDC hdc)
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->Render(hdc);
		}
		Render(hdc);
	}
	
	void CScene::AddGameObject(CGameObject* pGameObject)
	{
		m_vecGameObject.push_back(pGameObject);
	}
}