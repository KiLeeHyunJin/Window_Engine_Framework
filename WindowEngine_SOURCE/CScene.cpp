#include "CScene.h"
#include "Enums.h"
#include "CLayer.h"
#include "CGameObject.h"

//#include "CInputManager.h"
//#include "CCollisionManager.h"
//#include "CGameObject.h"

namespace Framework
{
	CScene::CScene()
	{
		m_vecLayer = {};
		m_vecLayer.resize((int)Enums::eLayerType::Size);
		for (UINT i = 0; i < m_vecLayer.size(); i++)
		{
			m_vecLayer[i] = new CLayer(i);
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
		Tick();

		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->Tick();
		}
	}

	void CScene::SceneLastTick()
	{
		LastTick();

		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->LastTick();
		}
	}

	void CScene::SceneDestroy()
	{
		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->Destroy();
		}
	}

	void CScene::SceneRender(HDC hdc)
	{
		//for (CLayer* pLayer : m_vecLayer)
		//{
		//	pLayer->Render(hdc);
		//}
		Render(hdc);

	}
	
	const CLayer* CScene::GetLayer(UINT layer) const
	{
		if (m_vecLayer.size() <= layer)
		{
			assert(1);
			return nullptr;
		}
		return m_vecLayer[layer];
	}

	void CScene::AddGameObject(CGameObject* pGameObject)
	{
		const UINT layer = pGameObject->GetLayerType();
		m_vecLayer[layer]->AddGameObject(pGameObject);
	}

	bool CScene::EraseInLayer(CGameObject* pGameObject)
	{
		const UINT objectLayer = pGameObject->GetLayerType();
		const bool result = m_vecLayer[objectLayer]->EraseInIndex(pGameObject);
		return result;
	}
	//void CScene::EraseGameObject(CGameObject* pGameObject)
	//{
	//	const Enums::eLayerType objectLayer = pGameObject->GetLayerType();
	//	m_vecLayer[(UINT)objectLayer]->EraseGameObject(pGameObject);
	//}
}