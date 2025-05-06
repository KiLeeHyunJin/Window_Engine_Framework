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
		//삭제하지 않을 요소를 앞으로 밀어내고, 한번만 erase()를 호출

		//알고리즘의 본래 목적과 코드의 명확성을 위해 부수 효과를 최소화고 분리
		auto newEnd = std::remove_if(m_vecActor.begin(), m_vecActor.end(), 
			[this](CActor* target)
			{
				const bool isDelete = target->GetSafeToDelete();
				if (isDelete)
				{
					m_vecRemoveActor.push_back(target); // 삭제 대기 목록에 추가
				}
				return isDelete;
			});


		if (newEnd != m_vecActor.end()) //살아있는 게임 오브젝트만 정리
		{
			// 리스트 정리 //필요없는 뒷 부분부터 마지막 까지 
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

			///삭제 예정이라면 삭제 목록으로 추가
			if (pActor->GetReserveDelete()) 
			{
				DeleteActor(pActor);
				iter = m_vecActor.erase(iter);
			}
			///활성화 되어있는 게임 오브젝트만 라스트 틱 호출
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

	void CLayer::ReleaseActor() //CCollisionManager에서 삭제 예약을 한꺼번에 제거
	{
		if (m_vecRemoveActor.empty())
			return; 

		// 제거할 객체 삭제
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

		// 제거할 객체 삭제
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

