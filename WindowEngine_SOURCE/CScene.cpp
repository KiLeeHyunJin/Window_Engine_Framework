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

	void CScene::Initialize()
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->Initialize();
		}
	}
	void CScene::Tick()
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->Tick();
		}
	}
	void CScene::LastTick()
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->LastTick();
		}
	}
	void CScene::Render(HDC hDC)
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->Render(hDC);
		}
	}
	void CScene::AddGameObject(CGameObject* pGameObject)
	{
		m_vecGameObject.push_back(pGameObject);
	}

	void CScene::Release()
	{
		for (CGameObject* gameObject : m_vecGameObject)
		{
			gameObject->Release();
		}
	}
}