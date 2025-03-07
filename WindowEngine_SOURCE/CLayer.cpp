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
		if (m_listGameObject.empty())
			return;

		// ������ ��ü�� ���� ���ɼ��� �ִٸ� reserve()�� �޸� ���Ҵ� ����ȭ
		//m_listRemoveGameObject.reserve(m_listRemoveGameObject.size() + m_listGameObject.size());

		for (auto iter = m_listGameObject.begin(); iter != m_listGameObject.end();)
		{
			CGameObject* pObj = *iter;
			CGameObject::eState state = pObj->GetState();

			if (pObj->GetReserveDelete())
			{
				pObj->SetSafeToDelete();
				m_listRemoveGameObject.push_back(pObj);
				iter = m_listGameObject.erase(iter);
			}
			else
			{
				if (state == CGameObject::eState::Enable)
				{
					pObj->LastTick();
				}
				++iter;
			}
		}
	}

	void CLayer::Render(HDC hdc) const
	{
		if (m_listGameObject.empty())
			return;

		for (const CGameObject* pGameObject : m_listGameObject)
		{
			if (pGameObject->GetState() == CGameObject::eState::Enable)
			{
				pGameObject->Render(hdc);;
			}
		}


	}

	void CLayer::Destroy()
	{
		if (m_listRemoveGameObject.empty())
			return; // ���ʿ��� ���� ����

		for (CGameObject* pGameObject : m_listRemoveGameObject)
		{
			pGameObject->Release();
			delete pGameObject;
		}

		m_listRemoveGameObject.clear();
		//m_listGameObject.shrink_to_fit(); // �ʿ��� ��� �޸� ����
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

