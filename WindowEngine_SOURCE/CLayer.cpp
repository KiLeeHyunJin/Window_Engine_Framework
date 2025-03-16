#include "CLayer.h"
#include "CGameObject.h"


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
	}

	void CLayer::Tick()
	{
		for (auto iter = m_listGameObject.cbegin();
			iter != m_listGameObject.cend();
			iter++)
		{
			const bool state = (*iter)->GetActive();
			if (state)
			{
				(*iter)->Tick();
			}
		}
	}

	void CLayer::LastTick()
	{
		if (m_listGameObject.empty())
			return;

		// 삭제할 개체가 많을 가능성이 있다면 reserve()로 메모리 재할당 최적화
		//m_listRemoveGameObject.reserve(m_listRemoveGameObject.size() + m_listGameObject.size());

		for (auto iter = m_listGameObject.begin(); iter != m_listGameObject.end();)
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
		}
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
			return; // 불필요한 연산 방지

		for (CGameObject* pGameObject : m_listRemoveGameObject)
		{
			pGameObject->Release();
			delete pGameObject;
		}

		m_listRemoveGameObject.clear();
		//m_listGameObject.shrink_to_fit(); // 필요할 경우 메모리 해제
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

