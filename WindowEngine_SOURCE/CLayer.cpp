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
		//요소를 앞으로 밀어내면서 한 번만 erase()를 호출하므로 더 빠름
		//std::vector<CGameObject*> toDelete; // 삭제할 객체를 저장하는 컨테이너

		auto newEnd = std::remove_if(m_listGameObject.begin(), m_listGameObject.end(),
			[=](CGameObject* target)
			{
				if (target->GetSafeToDelete()) 
				{
					m_listRemoveGameObject.push_back(target); // 삭제 대기 목록에 추가
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



		// 리스트 정리
		m_listGameObject.erase(newEnd, m_listGameObject.end());

	}

	void CLayer::LastTick()
	{
		// 삭제할 개체가 많을 가능성이 있다면 reserve()로 메모리 재할당 최적화
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

