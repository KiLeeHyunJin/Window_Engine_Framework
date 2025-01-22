#include "CLayer.h"


namespace Framework
{
	CLayer::CLayer(Enums::eLayerType layer) :
		m_listGameObject({}), 
		m_listRemoveGameObject({}),
		m_eLayer(layer)
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
		}
		m_listGameObject.clear();
	}

	void CLayer::Tick()
	{
		for (auto iter = m_listGameObject.cbegin();
			iter != m_listGameObject.cend();
			iter++)
		{
			CGameObject::eState state = (*iter)->GetState();
			if (state == CGameObject::eState::Enable)
			{
				(*iter)->Tick();
			}
		}
	}

	void CLayer::LastTick()
	{
		for (auto iter = m_listGameObject.cbegin();
			iter != m_listGameObject.cend();
			)
		{
			CGameObject* pObj = (*iter);
			CGameObject::eState state = pObj->GetState();

			if (state == CGameObject::eState::Enable)
			{
				(*iter)->LastTick();
			}
			else if (state == CGameObject::eState::Destory)
			{
				m_listRemoveGameObject.push_back(pObj);
				iter = m_listGameObject.erase(iter);
				continue;
			}

			iter++;
		}
	}

	void CLayer::Render(HDC hdc)
	{
		for (auto iter = m_listGameObject.cbegin();
			iter != m_listGameObject.cend();
			iter++)
		{
			CGameObject::eState state = (*iter)->GetState();
			if (state == CGameObject::eState::Enable)
			{
				(*iter)->Render(hdc);;
			}
		}
	}

	void CLayer::Destroy()
	{
		//std::erase_if(m_listRemoveGameObject,[](CGameObject* pObj){return pObj->GetDead()});

		for (auto iter = m_listRemoveGameObject.cbegin();
			iter != m_listRemoveGameObject.cend();)
		{
			CGameObject* eraseObj = (*iter);
			iter = m_listRemoveGameObject.erase(iter);

			RemoveGameObject(eraseObj);
		}
	}

	void CLayer::RemoveGameObject(CGameObject* pGameObject)
	{
		pGameObject->Release();
		delete pGameObject;
	}

	void CLayer::AddGameObject(CGameObject* pGameObject)
	{
		m_listGameObject.push_back(pGameObject);
	}

	void CLayer::EraseGameObject(CGameObject* pGameObject)
	{
		std::erase_if(m_listGameObject, 
			[=](CGameObject* pObj) 
			{
				return pObj == pGameObject;
			});
	}
}

