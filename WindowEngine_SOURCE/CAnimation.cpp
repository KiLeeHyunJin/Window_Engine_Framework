#include "CAnimation.h"

#include "CGameObject.h"
#include "CRenderer.h"

#include "CTransformComponent.h"
#include "CAnimatorComponent.h"
#include "CCameraComponent.h"

#include "CTimeManager.h"
#include "CInputManager.h"

namespace Framework
{

	 CAnimation::CAnimation() :
		CResource(Enums::eResourceType::Animation),
		m_pOwner(nullptr), m_pTexture(nullptr), m_vecSprites{},
		m_iIndex(-1), m_fTime(0), m_bCompleted(false) //, m_bLoop(false)
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
		CTransformComponent* pTr = pObj->GetTransformComponent();

		Vector2 originPos = pTr->GetPos();
		Vector2 pos = originPos;

		const Vector2 scale = pTr->GetScale();
		const float rot = pTr->GetRot();

		CCameraComponent* mainCam = Renderer::CRenderer::GetMainCamera();
		if (mainCam != nullptr)
		{
			pos = mainCam->CaluatePosition(pos);
			originPos = mainCam->CaluatePosition(originPos);
		}
		const Sprite sprite = m_vecSprites[m_iIndex];

		pos.AddX(sprite.size.GetX() * -0.5f);
		pos.AddY(sprite.size.GetY() * -0.5f);

		pos.AddX(sprite.offset.GetX());
		pos.AddY(sprite.offset.GetY());

		const int idx = (int)m_pTexture->GetTextureType();
		(this->*RenderFunc[idx])(hdc, rot, pos, scale, sprite);

		Rectangle(hdc, (UINT)(originPos.GetX() - 2), (UINT)(originPos.GetY() - 2), (UINT)(originPos.GetX() + 2), (UINT)(originPos.GetY() + 2));

		std::wstring pointStr = L"X : " + std::to_wstring((int)originPos.GetX()) + L", Y : " + std::to_wstring((int)originPos.GetY());
		int lenPos = (int)wcsnlen_s(pointStr.c_str(), 50);
		TextOut(hdc, (UINT)(originPos.GetX() + 10), (UINT)(originPos.GetY() - 15), pointStr.c_str(), lenPos);
	}



	void  CAnimation::RenderBMP(HDC hdc, float rot, Maths::Vector2 pos, Maths::Vector2 scale, const Sprite& sprite) const
	{
		HDC imgHdc = m_pTexture->GetHDC();

		if (m_pTexture->GetAlpha())
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;

			AlphaBlend(hdc,
				(UINT)pos.GetX() , (UINT)pos.GetY(),
				(UINT)(sprite.size.GetX() * scale.GetX()), (UINT)(sprite.size.GetY() * scale.GetY()),
				imgHdc,
				(UINT)sprite.leftTop.GetX(), (UINT)sprite.leftTop.GetY(),
				(UINT)sprite.size.GetX(), (UINT)sprite.size.GetY(),
				func);
		}
		else
		{
			TransparentBlt(hdc,
				(UINT)pos.GetX(), (UINT)pos.GetY(),
				(UINT)(sprite.size.GetX() * scale.GetX()), (UINT)(sprite.size.GetY() * scale.GetY()),
				imgHdc,
				(UINT)sprite.leftTop.GetX(), (UINT)sprite.leftTop.GetY(),
				(UINT)sprite.size.GetX(), (UINT)sprite.size.GetY(),
				RGB(255, 0, 255));
		}
	}

	void  CAnimation::RenderPNG(HDC hdc, float rot, Maths::Vector2 pos, Maths::Vector2 scale, const Sprite& sprite) const
	{
		//Gdiplus::ImageAttributes imgAtt = {};
		//imgAtt.SetColorKey(Gdiplus::Color(100, 100, 100), Gdiplus::Color(255, 255, 255));

		Gdiplus::Graphics graphics(hdc);

		graphics.TranslateTransform(pos.GetX(), pos.GetY());
		graphics.RotateTransform(rot);
		graphics.TranslateTransform(-pos.GetX(), -pos.GetY());

		Maths::Vector2 vecSize(sprite.size.GetX() * scale.GetX(), sprite.size.GetY() * scale.GetY());

		graphics.DrawImage(m_pTexture->GetImage(),
			Gdiplus::Rect(
				(UINT)pos.GetX(), (UINT)pos.GetY(),
				(UINT)vecSize.GetX(), (UINT)vecSize.GetY()),
			(UINT)sprite.leftTop.GetX(), (UINT)sprite.leftTop.GetY(),
			(UINT)vecSize.GetX(), (UINT)vecSize.GetY(),
			Gdiplus::UnitPixel,
			nullptr);
	}

	void  CAnimation::CreateAnimation(const std::wstring& name, CTexture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		m_pTexture = spriteSheet;
		SetName(name);
		for (UINT i = 0; i < spriteLength; i++)
		{
			Sprite sprite	= {};
			sprite.leftTop	= Vector2(leftTop.GetX() + (size.GetX() * i), leftTop.GetY());
			sprite.size		= size;
			sprite.offset	= offset;
			sprite.duration = duration;

			m_vecSprites.push_back(sprite);
		}
	}

}

