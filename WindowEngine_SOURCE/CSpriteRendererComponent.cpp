#pragma once
#include "CSpriteRendererComponent.h"
#include "CTransformComponent.h"
#include "CGameObject.h"
#include "CRenderer.h"

Framework::CSpriteRendererComponent::CSpriteRendererComponent() :
	CComponent(Enums::eComponentType::SpriteRenderer),
	m_pTexture(nullptr), m_vecScale(Maths::Vector2::One)
{
}

Framework::CSpriteRendererComponent::~CSpriteRendererComponent()
{
}

void Framework::CSpriteRendererComponent::Initialize()
{
}

void Framework::CSpriteRendererComponent::Release()
{
}

void Framework::CSpriteRendererComponent::Tick()
{
}

void Framework::CSpriteRendererComponent::LastTick()
{
}

void Framework::CSpriteRendererComponent::Render(HDC hdc)
{
	if (m_pTexture == nullptr)
		return;

	const CTransformComponent* tr = GetOwner()->GetComponent<CTransformComponent>();
	const Maths::Vector2 trPos  = tr->GetPos();
	const Maths::Vector2 pos = Renderer::mainCamera->CaluatePosition(trPos);

	const CTexture::eTextureType textureType = m_pTexture->GetTextureType();
	const UINT imgWidth = m_pTexture->GetWidth();
	const UINT imgHeight = m_pTexture->GetHeight();

	if (textureType == CTexture::eTextureType::Bmp)
	{
		TransparentBlt(
			hdc, 
			(INT)pos.x, (INT)pos.y,
			(INT)(imgWidth * m_vecScale.x), (INT)(imgHeight * m_vecScale.y),
			m_pTexture->GetHDC(), 0, 0, imgWidth, imgHeight, RGB(255,0,255));
	}
	else if (textureType == CTexture::eTextureType::Png)
	{
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(
			m_pTexture->GetImage(), 
			Gdiplus::Rect(
				(INT)pos.x, (INT)pos.y,
				(INT)(imgWidth * m_vecScale.x), (INT)(imgHeight * m_vecScale.y)));
	}

	return;

	HPEN redPen = CreatePen(BS_SOLID,2,RGB(255, 0, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)redPen);
	
	HBRUSH bluBrush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, (HGDIOBJ)bluBrush);



	Rectangle(hdc,
		(INT)(pos.x - 10), (INT)(pos.y - 10),
		(INT)(pos.x + 10), (INT)(pos.y + 10));
	
	SelectObject(hdc, (HGDIOBJ)oldPen);
	DeleteObject(redPen);
	
	SelectObject(hdc, (HGDIOBJ)oldBrush);
	DeleteObject(bluBrush);
}
