#include "CScene.h"
#include "CGameObject.h"
#include "Enums.h"

namespace Framework
{
	CScene::CScene()
	{
		m_vecLayer = {};
		m_vecLayer.resize((int)Enums::eLayerType::Size);
		for (size_t i = 0; i < m_vecLayer.size(); i++)
		{
			m_vecLayer[i] = new CLayer((Enums::eLayerType)i);
		}
	}

	CScene::~CScene()
	{
		for (size_t i = 0; i < m_vecLayer.size(); i++)
		{
			delete m_vecLayer[i];
		}
		m_vecLayer.clear();
	}
	void CScene::SceneInitialize()
	{
		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->Initialize();
		}
		Initialize();
	}
	void CScene::SceneRelease()
	{
		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->Release();
		}
		Release();
	}
	void CScene::SceneTick()
	{
		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->Tick();
		}
		Tick();
	}
	void CScene::SceneLastTick()
	{
		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->LastTick();
		}
		LastTick();
	}
	void CScene::SceneRender(HDC hdc)
	{
		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->Render(hdc);
		}
		Render(hdc);
	}
	
	void CScene::AddGameObject(CGameObject* pGameObject, Enums::eLayerType layer)
	{
		m_vecLayer[(int)layer]->AddGameObject(pGameObject);
	}
}