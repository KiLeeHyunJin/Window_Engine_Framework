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
		//삭제하지 않을 요소를 앞으로 밀어내고, 한번만 erase()를 호출

		//알고리즘의 본래 목적과 코드의 명확성을 위해 부수 효과를 최소화고 분리
		auto newEnd = std::remove_if(m_listGameObject.begin(), m_listGameObject.end(), 
			[this](CGameObject* target)
			{
				const bool isDelete = target->GetSafeToDelete();
				if (isDelete)
				{
					m_listRemoveGameObject.push_back(target); // 삭제 대기 목록에 추가
				}
				return isDelete;
			});


		if (newEnd != m_listGameObject.end()) //살아있는 게임 오브젝트만 정리
		{
			// 리스트 정리 //필요없는 뒷 부분부터 마지막 까지 
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

			///삭제 예정이라면 삭제 목록으로 추가
			if (pObj->GetReserveDelete()) 
			{
				DeleteGameObject(pObj);
				iter = m_listGameObject.erase(iter);
			}
			///활성화 되어있는 게임 오브젝트만 라스트 틱 호출
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

	void CLayer::Destroy() //CCollisionManager에서 삭제 예약을 한꺼번에 제거
	{
		if (m_listRemoveGameObject.empty())
			return; 

		// 제거할 객체 삭제
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

