#include "CButton.h"
#include "CInputManager.h"
#include "CRenderManager.h"
namespace Framework
{
	CButton::CButton() : 
		m_pTexture(nullptr), 
		m_eButtonState(eButtonState::None)
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
		
		RENDER::DrawRectangle(hdc, m_vecRenderPos, GetScale());

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
	void CButton::OnEnter()
	{
		m_colorFill = Color(0, 0, 255);
	}
	void CButton::OnExit()
	{
		m_colorFill = Color(255, 0, 255);
	}
}
