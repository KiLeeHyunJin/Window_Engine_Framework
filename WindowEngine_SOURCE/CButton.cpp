#include "CButton.h"
#include "Utils.h"
#include "CTimeManager.h"

namespace Framework
{
	CButton::CButton()
	{
	}

	CButton::~CButton()
	{
	}

	void CButton::OnInitialize()
	{
	}

	void CButton::OnRelease()
	{
	}

	void CButton::OnActive()
	{
	}

	void CButton::OnInActive()
	{
	}

	void CButton::OnTick()
	{
	}

	void CButton::OnLastTick()
	{
	}

	void CButton::OnClear()
	{
	}

	void CButton::OnRender(HDC hdc) const
	{
		HBRUSH newBrush = CreateSolidBrush(RGB(m_colorFill.r, m_colorFill.g, m_colorFill.b));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
		
		Utils::DrawRect(hdc, m_vecRenderPos, GetScale());

		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(newBrush);
	}

	void CButton::OnClick()
	{
		if (m_pOnClick != nullptr)
		{
			m_pOnClick();
		}
	}

	void CButton::OnDown()
	{
		if (m_pOnDown != nullptr)
		{
			m_pOnDown();
		}
	}

	void CButton::OnUp()
	{
		if (m_pOnUp != nullptr)
		{
			m_pOnUp();
		}

		if (m_fClickSumTime > CLICK_ALLOWABLE_TIME)
		{
			if (GetPrevDrag() == false)
			{
				OnClick();
			}
		}
		m_fClickSumTime = 0;
	}

	void CButton::OnEnter()
	{
		m_colorFill = Color(0, 0, 255);

		if (GetUIState() == eUIState::Pressed)
		{
			m_fClickSumTime += GET_SINGLE(TIME).DeltaTime();
		}
	}
	void CButton::OnExit()
	{
		m_colorFill = Color(255, 0, 255);
	}
}
