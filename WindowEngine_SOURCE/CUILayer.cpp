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

		m_vecUIs.push_back(pUI);
	}

	bool CUILayer::RemoveUI(CUIBase* pUI)
	{
		if (pUI == nullptr)
		{
			return false;
		}


	}


}
