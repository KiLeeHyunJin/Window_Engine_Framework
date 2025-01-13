#include "CAnimation.h"
#include "CTimeManager.h"
#include "CGameObject.h"
#include "CTransformComponent.h"
#include "CAnimatorComponent.h"
#include "CRenderer.h"
#include "CCameraComponent.h"

namespace Framework
{

	 CAnimation::CAnimation() :
		CResource(Enums::eResourceType::Animation),
		m_pOwner(nullptr), m_pTexture(nullptr), m_vecSprites{},
		m_iIndex(-1), m_fTime(0), m_bLoop(false), m_bCompleted(false)
	{
		RenderFunc[(int)CTexture::eTextureType::Bmp] = &CAnimation::RenderBMP;
		RenderFunc[(int)CTexture::eTextureType::Png] = &CAnimation::RenderPNG;
	}

	 CAnimation::~CAnimation()
	{
	}

	HRESULT  CAnimation::Load(const std::wstring& wstrPath)
	{
		return E_NOTIMPL;
	}

	void  CAnimation::Reset()
	{
		m_fTime = 0.0f;
		m_iIndex = 0;
		m_bCompleted = false;
	}

	void  CAnimation::Tick()
	{
		if (m_bCompleted)
		{
			return;
		}
		m_fTime += DELTATIME;
		if (m_vecSprites[m_iIndex].duration < m_fTime)
		{
			m_fTime = 0;
			if (m_iIndex < m_vecSprites.size() - 1)
			{
				m_iIndex++;
			}
			else
			{
				if (m_bCompleted == false)
				{
					m_bCompleted = true;
				}
			}
		}
	}

	void  CAnimation::Render(HDC hdc)
	{
		if (m_pTexture == nullptr)
		{
			return;
		}
		CGameObject* pObj = m_pOwner->GetOwner();
		CTransformComponent* pTr = pObj->GetComponent<CTransformComponent>();
		Vector2 pos = pTr->GetPos();
		const Vector2 scale = pTr->GetScale();
		const float rot = pTr->GetRot();

		if (Renderer::mainCamera)
		{
			pos = Renderer::mainCamera->CaluatePosition(pos);
		}

		CTexture::eTextureType textureType = m_pTexture->GetTextureType();
		Sprite sprite = m_vecSprites[m_iIndex];

		pos.x -= sprite.size.x * 0.5f;
		pos.y -= sprite.size.y * 0.5f;
		//auto func = RenderFunc[(int)textureType];
		//func;
		if (textureType == CTexture::eTextureType::Bmp)
		{
			RenderBMP(hdc, rot, pos, scale, sprite);
		}
		else if (textureType == CTexture::eTextureType::Png)
		{
			RenderPNG(hdc, rot, pos, scale, sprite);
		}
		//(RenderFunc[(int)textureType](hdc, rot, pos, scale, sprite));//(hdc, rot, pos, scale, sprite);
		
	}

	void  CAnimation::CreateAnimation(const std::wstring& name,  CTexture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		m_pTexture = spriteSheet;
		for (UINT i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop = Vector2(leftTop.x + (size.x * i), leftTop.y);
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			m_vecSprites.push_back(sprite);
		}

	}

	void  CAnimation::RenderBMP(HDC hdc, float rot, Maths::Vector2 pos, Maths::Vector2 scale, Sprite sprite)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		HDC imgHdc = m_pTexture->GetHDC();

		AlphaBlend(hdc,
			pos.x, pos.y,
			sprite.size.x * scale.x, sprite.size.y * scale.y,
			imgHdc,
			sprite.leftTop.x, sprite.leftTop.y,
			sprite.size.x, sprite.size.y,
			func);
	}

	void  CAnimation::RenderPNG(HDC hdc, float rot, Maths::Vector2 pos, Maths::Vector2 scale, Sprite sprite)
	{
		//Gdiplus::ImageAttributes imgAtt = {};
		//imgAtt.SetColorKey(Gdiplus::Color(100, 100, 100), Gdiplus::Color(255, 255, 255));

		Gdiplus::Graphics graphics(hdc);

		//graphics.TranslateTransform(pos.x, pos.y);
		//graphics.RotateTransform(rot);
		//graphics.TranslateTransform(-pos.x, -pos.y);

		graphics.DrawImage(m_pTexture->GetImage(),
			Gdiplus::Rect(
				(INT)pos.x, (INT)pos.y,
				(INT)sprite.size.x * scale.x, sprite.size.y * scale.y),
			sprite.leftTop.x, sprite.leftTop.y,
			sprite.size.x, sprite.size.y,
			Gdiplus::UnitPixel,
			nullptr);
	}


}

