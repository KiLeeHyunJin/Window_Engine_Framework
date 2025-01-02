#pragma once;
#include "CSpriteRenderer.h"
#include "CTransform.h"
#include "CGameObject.h"

Framework::CSpriteRenderer::CSpriteRenderer()
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
	
	HPEN redPen = CreatePen(BS_SOLID,2,RGB(255, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)redPen);
	
	HBRUSH bluBrush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, (HGDIOBJ)bluBrush);
	CTransform* tr = GetOwner()->GetComponent<CTransform>();

	int x = tr->GetX();
	int y = tr->GetY();

	Rectangle(hdc,
		x - 10, y - 10,
		x + 10, y + 10);
	
	SelectObject(hdc, (HGDIOBJ)oldPen);
	DeleteObject(redPen);
	
	SelectObject(hdc, (HGDIOBJ)oldBrush);
	DeleteObject(bluBrush);
}
