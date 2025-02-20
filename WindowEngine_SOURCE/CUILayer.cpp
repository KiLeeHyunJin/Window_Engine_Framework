#include "CUILayer.h"



namespace Framework
{

	CUILayer::CUILayer()
	{
	}

	CUILayer::~CUILayer()
	{
	}

	bool CUILayer::AddUI(CUIBase* pUI)
	{
		if (pUI == nullptr)
		{
			return false;
		}

		m_listUIs.push_back(pUI);
	}

	bool CUILayer::RemoveUI(CUIBase* pUI)
	{
		if (pUI == nullptr)
		{
			return false;
		}
		for (auto iter = m_listUIs.cbegin(); iter != m_listUIs.cend() ; iter++)
		{
			if (*iter == pUI)
			{
				m_listUIs.erase(iter);
				return true;
			}
		}
		return false;

	}


}
