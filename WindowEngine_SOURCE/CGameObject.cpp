#pragma once
#include "CGameObject.h"
#include "CInputManager.h"
#include "CTimeManager.h"

namespace Framework
{
	CGameObject::CGameObject()
	{
		m_fX = 0;
		m_fY = 0;
	}
	CGameObject::~CGameObject()
	{
	}

	void CGameObject::Initialize()
	{
	}

	void CGameObject::Tick()
	{
		float speed = 200;
		if (INPUT::GetKeyPressed(eKeyCode::Left))
		{
			m_fX -= speed * DELTATIME;
		}
		if (INPUT::GetKeyPressed(eKeyCode::Right))
		{
			m_fX += speed * DELTATIME;

		}
		if (INPUT::GetKeyPressed(eKeyCode::Up))
		{
			m_fY -= speed * DELTATIME;
		}
		if (INPUT::GetKeyPressed(eKeyCode::Down))
		{
			m_fY += speed * DELTATIME;
		}
	}

	void CGameObject::LastTick()
	{

	}
	
	void CGameObject::Render(HDC hdc) const
	{
		int x = (int)m_fX;
		int y = (int)m_fY;

		HPEN redPen = CreatePen(BS_SOLID,2,RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)redPen);

		HBRUSH bluBrush = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, (HGDIOBJ)bluBrush);
		Rectangle(hdc,
			x - 10, y - 10,
			x + 10, y + 10);

		SelectObject(hdc, (HGDIOBJ)oldPen);
		DeleteObject(redPen);

		SelectObject(hdc, (HGDIOBJ)oldBrush);
		DeleteObject(bluBrush);
	}
	void CGameObject::Release()
	{
	}
}