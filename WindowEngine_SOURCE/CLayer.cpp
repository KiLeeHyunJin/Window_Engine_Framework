#include "CLayer.h"
#include "CGameObject.h"
#include "Object.h"

#include "CSceneManager.h"
#include "CInputManager.h"

namespace Framework
{
	CLayer::CLayer(UINT layer) :
		m_listGameObject({}), 
		m_listRemoveGameObject({}),
		m_eLayer(layer)
	{	}

	CLayer::~CLayer()
	{	}

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
		//�������� ���� ��Ҹ� ������ �о��, �ѹ��� erase()�� ȣ��

		//�˰����� ���� ������ �ڵ��� ��Ȯ���� ���� �μ� ȿ���� �ּ�ȭ�� �и�
		auto newEnd = std::remove_if(m_listGameObject.begin(), m_listGameObject.end(), 
			[this](CGameObject* target)
			{
				const bool isDelete = target->GetSafeToDelete();
				if (isDelete)
				{
					m_listRemoveGameObject.push_back(target); // ���� ��� ��Ͽ� �߰�
				}
				return isDelete;
			});


		if (newEnd != m_listGameObject.end()) //����ִ� ���� ������Ʈ�� ����
		{
			// ����Ʈ ���� //�ʿ���� �� �κк��� ������ ���� 
			m_listGameObject.erase(newEnd, m_listGameObject.end());
		}


		for (CGameObject* pObj : m_listGameObject)
		{
			if (pObj->GetReserveDelete())
			{
				pObj->SetSafeToDelete();
			}
			else
			{
				if (pObj->GetActive())
				{
					const bool result = pObj->Tick();
					if (result == false)
					{
						Object::Destroy(pObj);
					}
				}
			}
		}
	}

	void CLayer::LastTick()
	{
		for (CGameObject* pObj : m_listGameObject)
		{
			if (pObj->GetActive() && 
				pObj->GetReserveDelete() == false)
			{
				const bool result = pObj->LastTick();
				if (result == false)
				{
					Object::Destroy(pObj);
				}
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
			if (pGameObject->GetActive() && 
				pGameObject->GetReserveDelete() == false)
			{
				pGameObject->Render(hdc);;
			}
		}
	}

	void CLayer::Destroy() //CCollisionManager���� ���� ������ �Ѳ����� ����
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

	bool CLayer::EraseInIndex(CGameObject* pGameObject)
	{
		auto iter = std::find(m_listGameObject.begin(), m_listGameObject.end(), pGameObject);
		const bool result = iter != m_listGameObject.end();

		if (result)
		{
			m_listGameObject.erase(iter);
		}

		/*auto iter = std::remove_if(m_listGameObject.begin(), m_listGameObject.end(),
			[pGameObject](CGameObject* obj) 
			{ return obj == pGameObject; });*/

		

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

