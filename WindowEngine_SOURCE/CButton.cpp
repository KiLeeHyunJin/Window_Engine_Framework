#include "CButton.h"
#include "CInputManager.h"

namespace Framework
{
	CButton::CButton() : Click(), m_pTexture(nullptr), m_eButtonState(eButtonState::None)
	{
	}
	CButton::~CButton()
	{
	}
	void CButton::OnInitialize()
	{
		Click[(int)eButtonState::Click] = &CButton::OnClick;
		Click[(int)eButtonState::Over]	= &CButton::OnOver;
		Click[(int)eButtonState::Out]	= &CButton::OnOut;
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

		const float halfX = (m_vecSize.x * 0.5f);
		const float halfY = (m_vecSize.y * 0.5f);

		Rectangle(hdc,
			m_vecPos.x - halfX, m_vecPos.y - halfX,
			m_vecPos.x + halfY, m_vecPos.y + halfY);

		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(newBrush);
	}


	void CButton::OnClick()
	{
	}
	void CButton::OnDown()
	{
	}
	void CButton::OnUp()
	{
	}
	void CButton::OnOver()
	{
		m_colorFill = Color(0, 0, 255);
	}
	void CButton::OnOut()
	{
		m_colorFill = Color(255, 0, 255);
	}
}
