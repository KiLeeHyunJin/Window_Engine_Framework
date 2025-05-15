#include "CLayer.h"
#include "CActor.h"
#include "Object.h"

#include "CSceneManager.h"
#include "CInputManager.h"

namespace Framework
{
	CLayer::CLayer(UINT layer) :
		m_vecActor({}), 
		m_vecRemoveActor({}),
		m_eLayer(layer)
	{	}

	CLayer::~CLayer()
	{	
	

	}

	void CLayer::Initialize()
	{
		for (CActor* pActor : m_vecActor)
		{
			if (pActor->GetParentID() != 0)
			{
				continue;
			}
			pActor->BeginPlay();
		}
	}

	void CLayer::Release()
	{
		for (CActor* pActor : m_vecActor)
		{
			if (pActor->GetParentID() == 0)
			{
				pActor->Release();
			}
		}
		for (CActor* pActor : m_vecRemoveActor)
		{
			if (pActor->GetParentID() == 0)
			{
				pActor->Release();
			}
		}
	}

	void CLayer::Delete()
	{
		for (CActor* pActor : m_vecActor)
		{
			GET_SINGLE(OBJECT).DeleteID(pActor);
			delete pActor;
		}
		m_vecActor.clear();

		for (CActor* pActor : m_vecRemoveActor)
		{
			delete pActor;
		}
		m_vecRemoveActor.clear();
	}
	void CLayer::Tick()
	{
		//�������� ���� ��Ҹ� ������ �о��, �ѹ��� erase()�� ȣ��

		//�˰����� ���� ������ �ڵ��� ��Ȯ���� ���� �μ� ȿ���� �ּ�ȭ�� �и�
		auto newEnd = std::remove_if(m_vecActor.begin(), m_vecActor.end(), 
			[this](CActor* target)
			{
				const bool isDelete = target->GetSafeToDelete();
				if (isDelete)
				{
					m_vecRemoveActor.push_back(target); // ���� ��� ��Ͽ� �߰�
				}
				return isDelete;
			});


		if (newEnd != m_vecActor.end()) //����ִ� ���� ������Ʈ�� ����
		{
			// ����Ʈ ���� //�ʿ���� �� �κк��� ������ ���� 
			m_vecActor.erase(newEnd, m_vecActor.end());
		}


		for (CActor* pActor : m_vecActor)
		{
			if (pActor->GetReserveDelete())
			{
				pActor->SetSafeToDelete();
			}
			else
			{
				if (pActor->GetParentID() != 0)
				{
					continue;
				}
				if (pActor->GetActive())
				{
					const bool result = pActor->Tick();
					if (result == false)
					{
						Object::Destroy(pActor);
					}
				}
			}
		}
	}

	void CLayer::LastTick()
	{
		for (CActor* pActor : m_vecActor)
		{
			if (pActor->GetParentID() != 0)
			{
				continue;
			}
			if (pActor->GetActive() && 
				pActor->GetReserveDelete() == false)
			{
				const bool result = pActor->LastTick();
				if (result == false)
				{
					Object::Destroy(pActor);
				}
			}
		}

		/*for (auto iter = m_vecActor.begin(); iter != m_vecActor.end();)
		{
			CActor* pActor = *iter;

			///���� �����̶�� ���� ������� �߰�
			if (pActor->GetReserveDelete()) 
			{
				DeleteActor(pActor);
				iter = m_vecActor.erase(iter);
			}
			///Ȱ��ȭ �Ǿ��ִ� ���� ������Ʈ�� ��Ʈ ƽ ȣ��
			else 
			{
				if (pActor->GetActive())
				{
					pActor->LastTickComponent();
				}
				++iter;
			}
		}*/
	}

	void CLayer::FixedTick()
	{
		if (m_vecActor.empty())
			return;

		for (CActor* pActor : m_vecActor)
		{
			if (pActor->GetParentID() != 0)
			{
				continue;
			}
			if (pActor->GetActive() &&
				pActor->GetReserveDelete() == false)
			{
				pActor->FixedTick();;
			}
		}
	}

	void CLayer::Render(HDC hdc) const
	{
		if (m_vecActor.empty())
			return;

		for (const CActor* pActor : m_vecActor)
		{
			if (pActor->GetParentID() != 0)
			{
				continue;
			}
			if (pActor->GetActive() && 
				pActor->GetReserveDelete() == false)
			{
				pActor->Render(hdc);;
			}
		}
	}

	void CLayer::ReleaseActor() //CCollisionManager���� ���� ������ �Ѳ����� ����
	{
		if (m_vecRemoveActor.empty())
			return; 

		// ������ ��ü ����
		for (CActor* pActor : m_vecRemoveActor)
		{
			if (pActor->GetParentID() != 0)
			{
				pActor->Release();
			}
		}
	}
	void CLayer::DeleteActor()
	{
		if (m_vecRemoveActor.empty())
			return;

		// ������ ��ü ����
		for (CActor* pActor : m_vecRemoveActor)
		{
			delete pActor;
		}
		m_vecRemoveActor.clear();
	}

	void CLayer::AddActor(CActor* pActor)
	{
		m_vecActor.push_back(pActor);
	}

	bool CLayer::EraseInIndex(CActor* pActor)
	{
		auto iter = std::find(m_vecActor.begin(), m_vecActor.end(), pActor);
		const bool result = iter != m_vecActor.end();

		if (result)
		{
			m_vecActor.erase(iter);
		}

		return result;
	}

	void CLayer::Clear()
	{
		for (auto actor : m_vecActor)
		{
			GET_SINGLE(EVENT).DeleteActor(actor);
		}
	}


	//void CLayer::EraseActor(CActor* pActor)
	//{
	//	std::erase_if(m_vecActor, 
	//		[=](CActor* pActor) 
	//		{
	//			return pActor == pActor;
	//		});
	//}
}

