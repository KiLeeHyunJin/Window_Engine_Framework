#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CUIBase;
	class CUIManager;
	class CUILayer
	{
	public:
		Enums::eUILayer GetLayer() { return m_eUILayer; }



		friend CUIManager;
	private:
		CUILayer();
		virtual ~CUILayer();
		
		void SetLayer(Enums::eUILayer eLayer) { m_eUILayer = eLayer; }

		bool AddUI(CUIBase* pUI);
		bool RemoveUI(CUIBase* pUI);

		std::list<CUIBase*> m_listUIs;

		Enums::eUILayer m_eUILayer;

	};

}


