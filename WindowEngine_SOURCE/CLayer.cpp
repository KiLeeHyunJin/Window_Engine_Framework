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
	{	}

	void CLayer::Initialize()
	{
		for (CActor* pObj : m_vecActor)
		{
			pObj->BeginPlay();
		}
	}

	void CLayer::Release()
	{
		for (CActor* pObj : m_vecActor)
		{
			pObj->Release();
			delete pObj;
		}
		m_vecActor.clear();

		for (CActor* pObj : m_vecRemoveActor)
		{
			pObj->Release();
			delete pObj;
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


		for (CActor* pObj : m_vecActor)
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
		for (CActor* pObj : m_vecActor)
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

		/*for (auto iter = m_vecActor.begin(); iter != m_vecActor.end();)
		{
			CActor* pObj = *iter;

			///삭제 예정이라면 삭제 목록으로 추가
			if (pObj->GetReserveDelete()) 
			{
				DeleteActor(pObj);
				iter = m_vecActor.erase(iter);
			}
			///활성화 되어있는 게임 오브젝트만 라스트 틱 호출
			else 
			{
				if (pObj->GetActive())
				{
					pObj->LastTickComponent();
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
			if (pActor->GetActive() && 
				pActor->GetReserveDelete() == false)
			{
				pActor->Render(hdc);;
			}
		}
	}

	void CLayer::DestroyActor() //CCollisionManager에서 삭제 예약을 한꺼번에 제거
	{
		if (m_vecRemoveActor.empty())
			return; 

		// 제거할 객체 삭제
		for (CActor* pObj : m_vecRemoveActor)
		{
			pObj->Release();
			delete pObj;
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
	//		[=](CActor* pObj) 
	//		{
	//			return pObj == pActor;
	//		});
	//}
}

