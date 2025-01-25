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

	const CTransformComponent* pTr = GetOwner()->GetTransformComponent();
	const Maths::Vector2 trPos  = pTr->GetPos();
	const Vector2 scale = pTr->GetScale();
	const float rot = pTr->GetRot();

	CCameraComponent* mainCam = Renderer::CRenderer::GetMainCamera();

	Maths::Vector2 pos = mainCam->CaluatePosition(trPos);

	const CTexture::eTextureType textureType = m_pTexture->GetTextureType();
	const UINT imgWidth = m_pTexture->GetWidth();
	const UINT imgHeight = m_pTexture->GetHeight();

	pos.x -= imgWidth * 0.5f;
	pos.y -= imgHeight * 0.5f;

	if (textureType == CTexture::eTextureType::Bmp)
	{
		if (m_pTexture->GetAlpha())
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;

			AlphaBlend(
				hdc,
				(INT)pos.x, (INT)pos.y,
				(INT)(imgWidth * m_vecScale.x * scale.x), (INT)(imgHeight * m_vecScale.y * scale.y),
				m_pTexture->GetHDC(), 0, 0, imgWidth, imgHeight,
				func);
		}
		else
		{
			TransparentBlt(
				hdc,
				(INT)pos.x, (INT)pos.y,
				(INT)(imgWidth * m_vecScale.x * scale.x), (INT)(imgHeight * m_vecScale.y * scale.y),
				m_pTexture->GetHDC(), 0, 0, imgWidth, imgHeight, RGB(255, 0, 255));
		}
	}
	else if (textureType == CTexture::eTextureType::Png)
	{
		Gdiplus::Graphics graphics(hdc);
		Gdiplus::ImageAttributes imgAtt = {};

		graphics.TranslateTransform(pos.x, pos.y);
		graphics.RotateTransform(rot);
		graphics.TranslateTransform(-pos.x, -pos.y);
		//imgAtt.SetColorKey();
		graphics.DrawImage(
			m_pTexture->GetImage(), 
			Gdiplus::Rect(
				(INT)pos.x, (INT)pos.y,
				(INT)(imgWidth * m_vecScale.x * scale.x), (INT)(imgHeight * m_vecScale.y * scale.y)),
			0, 0,
			imgWidth, imgHeight,
			Gdiplus::UnitPixel,
			nullptr); //&imgAtt;
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
