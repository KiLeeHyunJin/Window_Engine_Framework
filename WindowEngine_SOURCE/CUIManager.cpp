#include "CUIManager.h"
#include "CUIBase.h"

namespace Framework
{
	std::stack<CUIBase*> CUIManager::m_stackBase = {};
	std::queue<Enums::eUIType> CUIManager::m_queUIType = {};
	std::unordered_map<Enums::eUIType, CUIBase*> CUIManager::m_unmapUI = {};
	CUIBase* CUIManager::m_pCurrentUI = nullptr;


	CUIManager::CUIManager()
	{
	}
	CUIManager::~CUIManager()
	{
	}

	void CUIManager::Push(Enums::eUIType type)
	{
		m_queUIType.push(type);
	}

	void CUIManager::Pop(Enums::eUIType type)
	{
		if (m_stackBase.size() == 0)
		{
			return;
		}
		CUIBase* pUIBase = nullptr;
		while (m_stackBase.size() != 0)
		{
			pUIBase = m_stackBase.top();
			m_stackBase.pop();

		}
	}

	void CUIManager::OnLoad(Enums::eUIType type)
	{
		std::unordered_map<Enums::eUIType, CUIBase*>::iterator iter = m_unmapUI.find(type);
		if (iter == m_unmapUI.end())
		{
			OnFail();
			return;
		}
		OnComplete(iter->second);
	}

	void CUIManager::OnComplete(CUIBase* uiBase)
	{
		if (uiBase == nullptr)
		{
			return;
		}

		uiBase->Initialize();
		uiBase->Active();
		uiBase->Tick();

		if (uiBase->GetFullScreen())
		{
			std::stack<CUIBase*> uiBases = m_stackBase;
			while (uiBases.empty() == false)
			{
				CUIBase* pUIBase = uiBases.top();
				uiBases.pop();
				if (pUIBase != nullptr)
				{
					pUIBase->InActive();
				}
			}
		}

		m_stackBase.push(uiBase);
		m_pCurrentUI = nullptr;

	}
	void CUIManager::OnFail()
	{
		m_pCurrentUI = nullptr;
	}

	void CUIManager::Release()
	{
		for (auto ui : m_unmapUI)
		{
			ui.second->OnClear();
			delete ui.second;
		}
	}

	void CUIManager::Initialize()
	{
	}
	void CUIManager::Tick()
	{
		std::stack<CUIBase*> uiBases = m_stackBase;
		while (uiBases.empty() == false)
		{
			CUIBase* pUIBase = uiBases.top();
			uiBases.pop();
			if (pUIBase != nullptr)
			{
				pUIBase->Tick();

			}
		}

		if (m_queUIType.size() > 0)
		{
			Enums::eUIType requestUI = m_queUIType.front();
			m_queUIType.pop();
			OnLoad(requestUI);
		}
	}

	void CUIManager::LastTick()
	{
		std::stack<CUIBase*> uiBases = m_stackBase;
		while (uiBases.empty() == false)
		{
			CUIBase* pUIBase = uiBases.top();
			uiBases.pop();
			if (pUIBase != nullptr)
			{
				pUIBase->LastTick();

			}
		}
	}
	void CUIManager::Render(HDC hdc)
	{
		std::stack<CUIBase*> uiBases = m_stackBase;
		while (uiBases.empty() == false)
		{
			CUIBase* pUIBase = uiBases.top();
			uiBases.pop();
			if (pUIBase != nullptr)
			{
				pUIBase->Render(hdc);

			}
		}
	}
}