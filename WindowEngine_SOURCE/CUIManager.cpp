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
		CUIBase* rightButton = new CUIBase();

		m_unmapUI.insert(std::make_pair(Enums::eUIType::Button, leftButton));
	}


	void CUIManager::Push(Enums::eUIType type)
	{
		m_queUIType.push(type);
	}

	void CUIManager::Pop(Enums::eUIType type)
	{
		const UINT size = (UINT)m_vecCurrentUIs.size();

		if (size == 0)								{	return;	}

		UINT removeIndex = -1;
		for (UINT i = 0; i < size; i++)
		{
			CUIBase* pUI = m_vecCurrentUIs[i];
			if (pUI->GetType() == type)
			{
				removeIndex = i;
				auto iter = m_vecCurrentUIs.cbegin() + i;
				m_vecCurrentUIs.erase(iter);
				break;
			}
		}

		if (removeIndex < 0)						{	return;	}

		for (UINT i = removeIndex; i < size; i++)
		{	m_vecCurrentUIs[i]->SetUIIndex(i);	}
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
		for (const auto& ui : m_unmapUI)
		{
			ui.second->OnClear();
			delete ui.second;
		}
	}

	void CUIManager::Clear()
	{
		m_vecCurrentUIs.clear();
		while (m_queUIType.empty() == false)
		{
			m_queUIType.pop();
		}
	}

	CUIBase* CUIManager::GetCollisionUI(Maths::Vector2 checkPos)
	{
		const UINT size = (UINT)m_vecCurrentUIs.size() - 1;
		if (size < 0)							{	return nullptr;	}

		CUIBase* pUI = GetChildUI(m_vecCurrentUIs);
		return pUI;
	}

	void CUIManager::SetLastSibling(CUIBase* pFrontUI)
	{
		if (pFrontUI->GetDragable() == false)	{	return;	}

		const UINT size = (UINT)m_vecCurrentUIs.size();
		if (size <= 1 )							{	return;	} // 마지막 요소면 이동 불필요

		pFrontUI = CUIManager::GetParentUI(pFrontUI);
		const UINT currentIdx = pFrontUI->GetUIIndex();
		if (currentIdx == size - 1 && 
			currentIdx == -1)					{	return; }

		auto iter = std::find(m_vecCurrentUIs.cbegin(), m_vecCurrentUIs.cend(), pFrontUI);
		if (iter != m_vecCurrentUIs.cend()) 
		{
			CUIBase* save = *iter;
			m_vecCurrentUIs.erase(iter);               // 요소 삭제 (O(N))
			m_vecCurrentUIs.push_back(save);          // 뒤에 추가 (O(1))
		}

		for (UINT i = currentIdx; i < size; i++) //번호 다시 기입
		{
			m_vecCurrentUIs[i]->SetUIIndex(i);
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

		CUIBase* pUI = GetCollisionUI(INPUT::GetMousePosition());
		if (pUI != nullptr)
		{
			CButton* pButton = dynamic_cast<CButton*>(pUI);
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

	void CUIManager::MouseEvent(CUIBase* pUI, CUIBase* pChild)
	{
		
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
		const UINT childSize = vecUIs.size();
		std::queue<CUIBase*> queUIs;
		for (UINT i = 0; i < childSize; i++)
		{
			if (vecUIs[i]->m_bCurMouseOn)
			{
				queUIs.push(vecUIs[i]);
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