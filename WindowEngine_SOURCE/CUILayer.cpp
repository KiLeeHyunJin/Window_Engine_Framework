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
		{	return false;	}

		auto iter = std::find(m_listUIs.begin(), m_listUIs.end(), pUI);
		if (iter != m_listUIs.cend())
		{
			m_listUIs.push_back(pUI);
			return true;
		}

		return false;
	}

	bool CUILayer::RemoveUI(CUIBase* pUI)
	{
		if (pUI == nullptr)
		{	return false;	}

		auto iter = std::find(m_listUIs.begin(), m_listUIs.end(), pUI);
		
		if (iter != m_listUIs.cend())
		{
			m_listUIs.erase(iter);
			return true;
		}
		return false;
	}

	


}
