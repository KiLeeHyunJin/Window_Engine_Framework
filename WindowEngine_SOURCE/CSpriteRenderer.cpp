#pragma once
#include "CSpriteRenderer.h"
#include "CTransform.h"
#include "CGameObject.h"

Framework::CSpriteRenderer::CSpriteRenderer():
	m_pImg(nullptr),
	m_iHeight(0), m_iWidth(0)
{
}

Framework::CSpriteRenderer::~CSpriteRenderer()
{
}

void Framework::CSpriteRenderer::Initialize()
{
}

void Framework::CSpriteRenderer::Release()
{
}

void Framework::CSpriteRenderer::Tick()
{
}

void Framework::CSpriteRenderer::LastTick()
{
}

void Framework::CSpriteRenderer::Render(HDC hdc)
{
	CTransform* tr = GetOwner()->GetComponent<CTransform>();
	Vector2 pos = tr->GetPos();

	if (m_pImg != nullptr)
	{
		Gdiplus::Graphics graphic(hdc);
		graphic.DrawImage(m_pImg, Gdiplus::Rect(pos.x, pos.y, m_iWidth, m_iHeight));
		return;
	}

	HPEN redPen = CreatePen(BS_SOLID,2,RGB(255, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)redPen);
	
	HBRUSH bluBrush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, (HGDIOBJ)bluBrush);



	Rectangle(hdc,
		pos.x - 10, pos.y - 10,
		pos.x + 10, pos.y + 10);
	
	SelectObject(hdc, (HGDIOBJ)oldPen);
	DeleteObject(redPen);
	
	SelectObject(hdc, (HGDIOBJ)oldBrush);
	DeleteObject(bluBrush);
}

void Framework::CSpriteRenderer::ImageLoad(const std::wstring& path)
{
	m_pImg = Gdiplus::Image::FromFile(path.c_str());
	m_iWidth = m_pImg->GetWidth();
	m_iHeight = m_pImg->GetHeight();
}
