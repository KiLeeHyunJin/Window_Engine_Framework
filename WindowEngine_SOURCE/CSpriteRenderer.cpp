#pragma once
#include "CSpriteRenderer.h"
#include "CTransform.h"
#include "CGameObject.h"

Framework::CSpriteRenderer::CSpriteRenderer():
	CComponent()
	m_pTexture(nullptr), m_vecScale(Maths::Vector2::One)
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
	if (m_pTexture == nullptr)
		return;

	const CTransform* tr = GetOwner()->GetComponent<CTransform>();
	const Maths::Vector2 pos = tr->GetPos();

	const CTexture::eTextureType textureType = m_pTexture->GetTextureType();
	const UINT imgWidth = m_pTexture->GetWidth();
	const UINT imgHeight = m_pTexture->GetHeight();

	if (textureType == CTexture::eTextureType::Bmp)
	{
		TransparentBlt(
			hdc, pos.x, pos.y, imgWidth * m_vecScale.x, imgHeight * m_vecScale.y,
			m_pTexture->GetHDC(), 0, 0, imgWidth, imgHeight, RGB(255,0,255));
	}
	else if (textureType == CTexture::eTextureType::Png)
	{
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(
			m_pTexture->GetImage(), 
			Gdiplus::Rect(pos.x, pos.y, imgWidth * m_vecScale.x, imgHeight * m_vecScale.y));
	}

	return;

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
