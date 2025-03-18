#include "CLayer.h"
#include "CGameObject.h"

#include "CSceneManager.h"
#include "CInputManager.h"

namespace Framework
{
	CLayer::CLayer(UINT layer) :
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

		for (CGameObject* pObj : m_listRemoveGameObject)
		{
			pObj->Release();
			delete pObj;
		}
		m_listRemoveGameObject.clear();
	}

	void CLayer::Tick()
	{
		//��Ҹ� ������ �о�鼭 �� ���� erase()�� ȣ���ϹǷ� �� ����
		//std::vector<CGameObject*> toDelete; // ������ ��ü�� �����ϴ� �����̳�

		auto newEnd = std::remove_if(m_listGameObject.begin(), m_listGameObject.end(),
			[=](CGameObject* target)
			{
				if (target->GetSafeToDelete()) 
				{
					m_listRemoveGameObject.push_back(target); // ���� ��� ��Ͽ� �߰�
					return true;
				}

				if (target->GetReserveDelete()) 
				{
					target->SetSafeToDelete();
				}
				else if (target->GetActive()) 
				{
					target->Tick();
				}

				return false;
			});



		// ����Ʈ ����
		m_listGameObject.erase(newEnd, m_listGameObject.end());

	}

	void CLayer::LastTick()
	{
		// ������ ��ü�� ���� ���ɼ��� �ִٸ� reserve()�� �޸� ���Ҵ� ����ȭ
		//m_listRemoveGameObject.reserve(m_listRemoveGameObject.size() + m_listGameObject.size());

		for (CGameObject* pObj : m_listGameObject)
		{
			const bool state = pObj->GetActive();
			if (state)
			{
				pObj->LastTick();
			}
		}

		/*for (auto iter = m_listGameObject.begin(); iter != m_listGameObject.end();)
		{
			CGameObject* pObj = *iter;

			///���� �����̶�� ���� ������� �߰�
			if (pObj->GetReserveDelete()) 
			{
				DeleteGameObject(pObj);
				iter = m_listGameObject.erase(iter);
			}
			///Ȱ��ȭ �Ǿ��ִ� ���� ������Ʈ�� ��Ʈ ƽ ȣ��
			else 
			{
				if (pObj->GetActive())
				{
					pObj->LastTick();
				}
				++iter;
			}
		}*/
	}

	void CLayer::Render(HDC hdc) const
	{
		if (m_listGameObject.empty())
			return;

		for (const CGameObject* pGameObject : m_listGameObject)
		{
			if (pGameObject->GetActive())
			{
				pGameObject->Render(hdc);;
			}
		}
	}

	void CLayer::Destroy()
	{
		if (m_listRemoveGameObject.empty())
			return; 

		// ������ ��ü ����
		for (CGameObject* pObj : m_listRemoveGameObject)
		{
			pObj->Release();
			delete pObj;
		}

		m_listRemoveGameObject.clear();
	}

	void CLayer::AddGameObject(CGameObject* pGameObject)
	{
		m_listGameObject.push_back(pGameObject);
	}

	void CLayer::DeleteGameObject(CGameObject* pGameObject)
	{
		pGameObject->SetSafeToDelete();
		m_listRemoveGameObject.push_back(pGameObject);
	}

	bool CLayer::EraseInIndex(CGameObject* pGameObject)
	{
		bool result = false;
		auto iter = std::remove_if(m_listGameObject.begin(), m_listGameObject.end(),
			[pGameObject](CGameObject* obj) 
			{ return obj == pGameObject; });

		if (iter != m_listGameObject.end()) 
		{
			m_listGameObject.erase(iter, m_listGameObject.end());
			result = true;
		}
		return result;
	}


	//void CLayer::EraseGameObject(CGameObject* pGameObject)
	//{
	//	std::erase_if(m_listGameObject, 
	//		[=](CGameObject* pObj) 
	//		{
	//			return pObj == pGameObject;
	//		});
	//}
}

