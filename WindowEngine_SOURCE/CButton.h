#pragma once
#include "CUIBase.h"
#include "CTexture.h"

namespace Framework
{
	class CUIManager;

	class CButton :
		public CUIBase
	{
	public:
		enum class eButtonState
		{
			None,
			Over,
			Click,
			Out,
			Size
		};
		CButton();
		virtual ~CButton();

		friend CUIManager;
	private:
		virtual void OnInitialize() override;
		virtual void OnRelease() override;

		virtual void OnActive()override;
		virtual void OnInActive()override;
		
		virtual void OnTick()override;
		virtual void OnLastTick()override;
		
		virtual void OnClear()override;
		virtual void OnRender(HDC hdc) override;

		virtual void OnClick() override;
		
		virtual void OnDown() override;
		virtual void OnUp() override;

		virtual void OnOver() override;
		virtual void OnOut() override;

		Resource::CTexture* m_pTexture;
		void (CButton::*Click[(int)eButtonState::Size])();
		eButtonState m_eButtonState;
		Color m_colorFill;

		//Event m_eClick;
	};


}

