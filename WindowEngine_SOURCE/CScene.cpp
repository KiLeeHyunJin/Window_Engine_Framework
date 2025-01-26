#include "CScene.h"
#include "CGameObject.h"
#include "Enums.h"

#include "CInputManager.h"

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

	void CScene::SceneDestroy()
	{
		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->Destroy();
		}
	}

	void CScene::SceneRender(HDC hdc)
	{
		for (CLayer* pLayer : m_vecLayer)
		{
			pLayer->Render(hdc);
		}
		Render(hdc);


		const Maths::Vector2 mousePos = CInputManager::GetMousePosition();
		
		const UINT mouseXPos = (UINT)mousePos.GetX();
		const UINT mouseYPos = (UINT)mousePos.GetY();

		std::wstring pointStr = L"X : " + std::to_wstring(mouseXPos) + L", Y : " + std::to_wstring(mouseYPos);
		UINT lenPos = (UINT)wcsnlen_s(pointStr.c_str(), 50);
		TextOut(hdc, mouseXPos + 10, mouseYPos - 15, pointStr.c_str(), lenPos);
	}
	
	void CScene::AddGameObject(CGameObject* pGameObject)
	{
		Enums::eLayerType layer = pGameObject->GetLayerType();
		m_vecLayer[(int)layer]->AddGameObject(pGameObject);
	}

	void CScene::EraseGameObject(CGameObject* pGameObject)
	{
		const Enums::eLayerType objectLayer = pGameObject->GetLayerType();
		m_vecLayer[(UINT)objectLayer]->EraseGameObject(pGameObject);
	}
}