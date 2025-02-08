#include "CUIManager.h"
#include "CUIBase.h"
#include "CButton.h"
#include "CInputManager.h"

namespace Framework
{
	std::queue<Enums::eUIType>						CUIManager::m_queUIType				= {};
	std::unordered_map<Enums::eUIType, CUIBase*>	CUIManager::m_unmapUI				= {};
	std::vector<CUIBase*>							CUIManager::m_vecCurrentUIs			= {};
	CUIBase*										CUIManager::m_pCurrentUI			= nullptr;


	CUIManager::CUIManager()
	{	}
	CUIManager::~CUIManager()
	{	}

	void CUIManager::Initialize()
	{
		CUIBase* leftButton = new CUIBase();
		leftButton->SetChangeHierarchy(true);

		CUIBase* rightButton = new CUIBase();
		leftButton->SetDrag(true);
		rightButton->SetChangeHierarchy(true);

		leftButton->SetType(Enums::eUIType::Button);
		rightButton->SetType(Enums::eUIType::Size);

		m_unmapUI.insert(std::make_pair(Enums::eUIType::Button, leftButton));
		m_unmapUI.insert(std::make_pair(Enums::eUIType::Size, rightButton));
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
		INT removeIndex = findIter->second->GetUIIndex();

		if (removeIndex < 0 || 
			m_vecCurrentUIs[removeIndex]->GetType() != type)
		{
			for (INT i = 0; i < size; i++)
			{
				CUIBase* pUI = m_vecCurrentUIs[i];
				if (pUI->GetType() == type)
				{
					removeIndex = i;
					break;
				}
			}
			removeIndex = -1;
		}

		if (removeIndex <= -1)						{	return;	}


		auto eraseIter = m_vecCurrentUIs.begin() + removeIndex;
		if (eraseIter != m_vecCurrentUIs.cend())
		{
			m_vecCurrentUIs.erase(eraseIter);
		}

		for (INT i = removeIndex; i < size - 1; i++)
		{	m_vecCurrentUIs[i]->SetUIIndex(i);	}
	}

	void CUIManager::Pop(CUIBase* closeUI)
	{
		const UINT closeUIIdx = closeUI->GetUIIndex();
		const UINT size = (UINT)m_vecCurrentUIs.size();

		if (size == 0) { return; }

		const auto iter = m_vecCurrentUIs.begin() + closeUIIdx;
		m_vecCurrentUIs.erase(iter);

		for (UINT i = closeUIIdx; i < size; i++)
		{
			m_vecCurrentUIs[i]->SetUIIndex(i);
		}

		closeUI->SetUIIndex(-1);
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

	CUIBase* CUIManager::GetCollisionUI()
	{
		const UINT size = (UINT)m_vecCurrentUIs.size() - 1;
		if (size < 0)							{	return nullptr;	}

		CUIBase* pUI = GetChildUI(m_vecCurrentUIs);
		return pUI;
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
		const UINT size = (UINT)m_vecCurrentUIs.size();

		for (UINT i = 0; i < size; i++)
		{
			m_vecCurrentUIs[i]->Tick();
		}

		if (m_queUIType.size() > 0)
		{
			Enums::eUIType requestUI = m_queUIType.front();
			m_queUIType.pop();
			OnLoad(requestUI);
		}
		CUIBase* pTargetUI = GetCollisionUI();

		if (pTargetUI != m_pCurrentUI)
		{
			m_pCurrentUI = pTargetUI;
		}


		for (UINT i = 0; i < size; i++)
		{
			MouseEvent(m_vecCurrentUIs[i], m_pCurrentUI);
		}
	}

	void CUIManager::LastTick()
	{
		const UINT size = (UINT)m_vecCurrentUIs.size();
		for (UINT i = 0; i < size; i++)
		{
			m_vecCurrentUIs[i]->LastTick();
		}
	}

	void CUIManager::Render(HDC hdc)
	{
		const UINT size = (UINT)m_vecCurrentUIs.size();
		for (UINT i = 0; i < size; i++)
		{
			m_vecCurrentUIs[i]->Render(hdc);
		}
	}

	void CUIManager::MouseEvent(CUIBase* pUI, CUIBase* pfocusUI)
	{
		if (pUI == pfocusUI)
		{
			pUI->Enter();
			pUI->Over();

			if (INPUT::GetKeyDown(eKeyCode::LBUTTON))
			{
				pUI->Down();
			}
			else if (INPUT::GetKeyUp(eKeyCode::LBUTTON))
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

	CUIBase* CUIManager::GetChildUI(const std::vector<CUIBase*>& vecUIs)
	{
		if (vecUIs.size() == 0)				{	return nullptr;	}

		std::queue<CUIBase*> queUIs;
		for(auto iter  = m_vecCurrentUIs.rbegin(); 
				 iter != m_vecCurrentUIs.rend(); 
				 ++iter)
		{
			if ((*iter)->m_bCurMouseOn)
			{
				queUIs.push(*iter);
				break;
			}
		}

		if (queUIs.empty())					{	return nullptr;	}

		CUIBase* targetUI = nullptr;

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