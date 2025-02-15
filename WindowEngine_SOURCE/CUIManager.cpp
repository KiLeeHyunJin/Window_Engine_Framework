#include "CUIManager.h"
#include "CUIBase.h"
#include "CButton.h"
#include "CInputManager.h"

namespace Framework
{
	std::queue<Enums::eUIType>						CUIManager::m_queUIType				= {};
	std::unordered_map<Enums::eUIType, CUIBase*>	CUIManager::m_unmapUI				= {};
	std::vector<CUIBase*>							CUIManager::m_vecCurrentUIs			= {};
	std::stack<CUIBase*>							CUIManager::m_vecCurrentPopups		= {};
	CUIBase*										CUIManager::m_pCurrentUI			= nullptr;


	CUIManager::CUIManager()
	{	}
	CUIManager::~CUIManager()
	{	}

	void CUIManager::Initialize()
	{
		
	}

	void CUIManager::LoadUI(Enums::eUIType type, CUIBase* pUI, bool bChangeHierarchy, bool bDrag)
	{
		pUI->SetDrag(bDrag);
		pUI->SetChangeHierarchy(bChangeHierarchy);
		pUI->SetType(type);
		m_unmapUI.insert(std::make_pair(type, pUI));
	}

	void CUIManager::Push(Enums::eUIType type)
	{
		m_queUIType.push(type);
	}

	void CUIManager::Pop(Enums::eUIType type)
	{
		const INT size = (INT)m_vecCurrentUIs.size();
		if (size == 0)								{	return;	}

		const auto& findIter = m_unmapUI.find(type);
		const CUIBase* findUI = findIter->second;
		INT closeUIIdx = findIter->second->GetUIIndex();

		if (closeUIIdx < 0 ||
			m_vecCurrentUIs[closeUIIdx]->GetType() != type)
		{
			closeUIIdx = FindUIIdex(findUI);
		}

		if (closeUIIdx <= -1)						{	return;	}

		CloseUI(closeUIIdx);
	}

	void CUIManager::Pop(CUIBase* closeUI)
	{
		const UINT size = (UINT)m_vecCurrentUIs.size();
		if (size == 0)								{	return; }

		INT closeUIIdx = closeUI->GetUIIndex();
		const Enums::eUIType type = closeUI->GetType();

		if (closeUIIdx < 0 ||
			m_vecCurrentUIs[closeUIIdx]->GetType() != type)
		{
			closeUIIdx = FindUIIdex(closeUI);
		}
		if (closeUIIdx < 0)							{ return; }

		CloseUI(closeUIIdx);
	}

	INT CUIManager::FindUIIdex(const CUIBase* pTarget)
	{
		const UINT size = (UINT)m_vecCurrentUIs.size();

		for (UINT i = 0; i < size; i++)
		{
			if (pTarget == m_vecCurrentUIs[i])
			{
				return i;
			}
		}
		return -1;
	}

	void CUIManager::CloseUI(INT closeUIIdx)
	{
		const auto iter = m_vecCurrentUIs.cbegin() + closeUIIdx;
		if (iter != m_vecCurrentUIs.cend())
		{
			(*iter)->SetUIIndex(-1);
			m_vecCurrentUIs.erase(iter);
		}

		UINT size = (UINT)m_vecCurrentUIs.size();
		for (UINT i = closeUIIdx; i < size; i++)
		{
			m_vecCurrentUIs[i]->SetUIIndex(i);
		}
	}

	void CUIManager::OnLoad(Enums::eUIType type)
	{
		std::unordered_map<Enums::eUIType, CUIBase*>::iterator iter = m_unmapUI.find(type);
		if (iter == m_unmapUI.end())
		{
			OnFail();
		}
		else
		{
			OnComplete(iter->second);
		}
	}

	void CUIManager::OnComplete(CUIBase* uiBase)
	{
		if (uiBase == nullptr)						{	return;	}

		uiBase->Initialize();
		uiBase->Active();
		uiBase->Tick();

		if (uiBase->GetFullScreen())
		{
			const UINT size = (UINT)m_vecCurrentUIs.size();
			for (UINT i = 0; i < size; i++)
			{
				m_vecCurrentUIs[i]->InActive();
			}
		}

		const UINT uiIdx = (UINT)m_vecCurrentUIs.size();
		uiBase->SetUIIndex(uiIdx);

		m_vecCurrentUIs.push_back(uiBase);
		m_pCurrentUI = nullptr;
	}

	void CUIManager::OnFail()
	{
		m_pCurrentUI = nullptr;
	}

	void CUIManager::Release()
	{
		Clear();

		for (auto& ui : m_unmapUI)
		{
			ui.second->Clear();
			ui.second->Release();
			delete ui.second;
		}
	}

	void CUIManager::Clear()
	{
		m_pCurrentUI = nullptr;
		m_vecCurrentUIs.clear();
		while (m_queUIType.empty() == false)
		{
			m_queUIType.pop();
		}
	}

	void CUIManager::SetLastSibling(CUIBase* pUI)
	{
		CUIBase* pParentUI = GetParentUI(pUI);
		if (pParentUI == nullptr)						{	return;	}
		if (pParentUI->GetChangeHierarchy() == false)	{	return;	}

		const UINT size = (UINT)m_vecCurrentUIs.size();
		const UINT currentIdx = pParentUI->GetUIIndex();

		if  (size <= 1  || 
			(size - 1) == currentIdx)					{	return;	} // 마지막 요소면 이동 불필요


		auto iter = m_vecCurrentUIs.cbegin() + currentIdx;
		if (iter != m_vecCurrentUIs.cend()) 
		{
			CUIBase* save = *iter;
			m_vecCurrentUIs.erase(iter);               // 요소 삭제 (O(N))
			m_vecCurrentUIs.push_back(save);          // 뒤에 추가 (O(1))

			for (UINT i = currentIdx; i < size; i++) //번호 다시 기입
			{
				m_vecCurrentUIs[i]->SetUIIndex(i);
			}
		}
	}


	void CUIManager::Tick()
	{
		for (auto& pUI : m_vecCurrentUIs)
		{
			pUI->Tick();
		}

		if (m_queUIType.size() > 0)
		{
			Enums::eUIType requestUI = m_queUIType.front();
			m_queUIType.pop();
			OnLoad(requestUI);
		}

		CUIBase* pTargetUI = GetFocusUI();
		if (m_pCurrentUI == nullptr)
		{
			m_pCurrentUI = pTargetUI;
		}
		else
		{
			if (m_pCurrentUI->m_bCurMouseOn == false)
			{
				m_pCurrentUI = pTargetUI;
			}
			else
			{
				if (pTargetUI != nullptr && 
					pTargetUI != m_pCurrentUI)
				{
					const CUIBase* pPrevParent = GetParentUI(m_pCurrentUI);
					const CUIBase* pNewParent = GetParentUI(pTargetUI);

					if (pPrevParent->m_iIndex <= pNewParent->m_iIndex)
					{
						m_pCurrentUI = pTargetUI;
					}
				}
			}
		}

		for (auto& pUI : m_vecCurrentUIs)
		{
			MouseEvent(pUI, m_pCurrentUI);
		}
	}

	void CUIManager::LastTick()
	{
		for (auto& pUI : m_vecCurrentUIs)
		{
			pUI->LastTick();
		}
	}

	void CUIManager::Render(HDC hdc)
	{
		for (const auto& pUI : m_vecCurrentUIs)
		{
			pUI->Render(hdc);
		}
	}

	void CUIManager::MouseEvent(CUIBase* pUI, CUIBase* pfocusUI)
	{
		if (pUI == pfocusUI)
		{
			pUI->Enter();
			pUI->Over();

			if (CInputManager::GetKeyDown(eKeyCode::LBUTTON))
			{
				pUI->Down();
			}
			else if (CInputManager::GetKeyUp(eKeyCode::LBUTTON))
			{
				pUI->Up();
			}
		}
		else
		{
			pUI->Exit();
		}

		for (CUIBase* pChildUI : pUI->m_vecChilds)
		{
			MouseEvent(pChildUI, pfocusUI);
		}
	}

	CUIBase* CUIManager::GetTopUI()
	{
		if (m_vecCurrentUIs.empty() == false) 
		{
			for (auto it = m_vecCurrentUIs.rbegin(); it != m_vecCurrentUIs.rend(); ++it) 
			{
				if ((*it)->m_bCurMouseOn) 
				{
					return *it;
				}
			}
		}
		return nullptr;
	}

	CUIBase* CUIManager::GetParentUI(CUIBase* pChild)
	{
		if (pChild == nullptr)				{	return nullptr; }

		CUIBase* pParent = pChild;
		if (pChild->m_pParent != nullptr)
		{
			while (pParent->m_pParent != nullptr)
			{
				pParent = pParent->m_pParent;
			}
		}
		return pParent;
	}

	CUIBase* CUIManager::GetFocusUI()
	{
		CUIBase* pTopUI = GetTopUI();
		if (pTopUI == nullptr)				{ return nullptr; }
		if (m_vecCurrentUIs.size() == 0)	{ return nullptr; }

		std::queue<CUIBase*> queUIs;
		queUIs.push(pTopUI);

		CUIBase* targetUI = nullptr;
		//for(auto iter  = m_vecCurrentUIs.cbegin(); 
		//		 iter != m_vecCurrentUIs.cend(); 
		//		 ++iter)
		//{
		//	if ((*iter)->m_bCurMouseOn)
		//	{
		//		queUIs.push(*iter);
		//		targetUI = *iter;
		//		//break;
		//	}
		//}

		//if (queUIs.empty())					{	return nullptr;	}


		while (queUIs.empty() == false)
		{
			CUIBase* pUI = queUIs.front();
			queUIs.pop();

			if (pUI->m_bCurMouseOn)
			{
				targetUI = pUI;
				const auto& targetChilds = pUI->m_vecChilds;
				
				for (UINT i = 0; i < targetChilds.size(); i++)
				{
					queUIs.push(targetChilds[i]);
				}
			}
		}
		return targetUI;
	}





}