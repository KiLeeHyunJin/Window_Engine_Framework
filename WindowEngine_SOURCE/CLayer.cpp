#include "CLayer.h"
#include "CActor.h"
#include "Object.h"

#include "CSceneManager.h"
#include "CInputManager.h"

namespace Framework
{
	CLayer::CLayer(UINT layer) :
		m_listActor({}), 
		m_listRemoveActor({}),
		m_eLayer(layer)
	{	}

	CLayer::~CLayer()
	{	}

	void CLayer::Initialize()
	{
		for (CActor* pObj : m_listActor)
		{
			pObj->BeginPlay();
		}
	}

	void CLayer::Release()
	{
		for (CActor* pObj : m_listActor)
		{
			pObj->Release();
			delete pObj;
		}
		m_listActor.clear();

		for (CActor* pObj : m_listRemoveActor)
		{
			pObj->Release();
			delete pObj;
		}
		m_listRemoveActor.clear();
	}

	void CLayer::Tick()
	{
		//�������� ���� ��Ҹ� ������ �о��, �ѹ��� erase()�� ȣ��

		//�˰����� ���� ������ �ڵ��� ��Ȯ���� ���� �μ� ȿ���� �ּ�ȭ�� �и�
		auto newEnd = std::remove_if(m_listActor.begin(), m_listActor.end(), 
			[this](CActor* target)
			{
				const bool isDelete = target->GetSafeToDelete();
				if (isDelete)
				{
					m_listRemoveActor.push_back(target); // ���� ��� ��Ͽ� �߰�
				}
				return isDelete;
			});


		if (newEnd != m_listActor.end()) //����ִ� ���� ������Ʈ�� ����
		{
			// ����Ʈ ���� //�ʿ���� �� �κк��� ������ ���� 
			m_listActor.erase(newEnd, m_listActor.end());
		}


		for (CActor* pObj : m_listActor)
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
		for (CActor* pObj : m_listActor)
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

		/*for (auto iter = m_listActor.begin(); iter != m_listActor.end();)
		{
			CActor* pObj = *iter;

			///���� �����̶�� ���� ������� �߰�
			if (pObj->GetReserveDelete()) 
			{
				DeleteActor(pObj);
				iter = m_listActor.erase(iter);
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
		if (m_listActor.empty())
			return;

		for (const CActor* pActor : m_listActor)
		{
			if (pActor->GetActive() && 
				pActor->GetReserveDelete() == false)
			{
				pActor->Render(hdc);;
			}
		}
	}

	void CLayer::Destroy() //CCollisionManager���� ���� ������ �Ѳ����� ����
	{
		if (m_listRemoveActor.empty())
			return; 

		// ������ ��ü ����
		for (CActor* pObj : m_listRemoveActor)
		{
			pObj->Release();
			delete pObj;
		}

		m_listRemoveActor.clear();
	}

	void CLayer::AddActor(CActor* pActor)
	{
		m_listActor.push_back(pActor);
	}

	bool CLayer::EraseInIndex(CActor* pActor)
	{
		auto iter = std::find(m_listActor.begin(), m_listActor.end(), pActor);
		const bool result = iter != m_listActor.end();

		if (result)
		{
			m_listActor.erase(iter);
		}

		/*auto iter = std::remove_if(m_listActor.begin(), m_listActor.end(),
			[pActor](CActor* obj) 
			{ return obj == pActor; });*/

		

		return result;
	}


	//void CLayer::EraseActor(CActor* pActor)
	//{
	//	std::erase_if(m_listActor, 
	//		[=](CActor* pObj) 
	//		{
	//			return pObj == pActor;
	//		});
	//}
}

