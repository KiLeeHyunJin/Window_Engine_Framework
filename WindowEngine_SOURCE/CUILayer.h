#pragma once

namespace Framework
{
	class CUIBase;
	class CUIManager;
	class CUILayer
	{
	public:
		friend CUIManager;
	private:
		CUILayer();
		virtual ~CUILayer();

		void AddUI(CUIBase* pUI);
		void RemoveUI(CUIBase* pUI);





	};

}


