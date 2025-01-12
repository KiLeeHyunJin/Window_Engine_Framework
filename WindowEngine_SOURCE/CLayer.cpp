#include "CLayer.h"


namespace Framework
{
	CLayer::CLayer(Enums::eLayerType layer) :
		m_listGameObject({}), m_eLayer(layer)
	{
	}

	CLayer::~CLayer()
	{
	}

	void CLayer::Initialize()
	{
		for (CGameObject* pObj : m_listGameObject)
		{
			pObj->Initialize();
		}
	}

	void CLayer::Release()
	{
		for (CGameObject* pObj : m_listGameObject)
		{
			pObj->Release();
			delete pObj;
			pObj = nullptr;
		}
		m_listGameObject.clear();
	}

	void CLayer::Tick()
	{
		for (CGameObject* pObj : m_listGameObject)
		{
			pObj->Tick();
		}
	}

	void CLayer::LastTick()
	{
		for (CGameObject* pObj : m_listGameObject)
		{
			pObj->LastTick();
		}
	}

	void CLayer::Render(HDC hdc)
	{
		for (CGameObject* pObj : m_listGameObject)
		{
			pObj->Render(hdc);
		}
	}

	void CLayer::AddGameObject(CGameObject* pGameObject)
	{
		m_listGameObject.push_back(pGameObject);
	}

}

