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
		m_pOwner(nullptr), m_pTexture(nullptr), m_vecSprites{},m_fDuration(0),
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
		if (m_fDuration < m_fTime)
		{
			m_fTime = 0;
			if (m_iIndex < (INT)m_vecSprites.size() - 1)
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
		{	return;	 }

		const CGameObject* pObj = m_pOwner->GetOwner();
		const CTransformComponent* pTr = pObj->GetTransformComponent();
		Vector2 pos = pTr->GetPos() + m_pTexture->GetOffset();


		const CCameraComponent* mainCam = Renderer::CRenderer::GetMainCamera();
		if (mainCam != nullptr)
		{	pos = mainCam->CaluatePosition(pos);	}

		const int idx = (int)m_pTexture->GetTextureType();
		const Sprite& sprite = m_vecSprites[m_iIndex];
		const Vector2& scale = pTr->GetScale();
		const float rot = pTr->GetRot();

		(this->*RenderFunc[idx])(hdc, rot, pos, scale, sprite);

	}



	void  CAnimation::RenderBMP(HDC hdc, float rot, const Maths::Vector2& pos, const Maths::Vector2& scale, const Sprite& sprite) const
	{
		HDC imgHdc = m_pTexture->GetHDC();
		const auto& sizes = m_pTexture->GetSpriteSize();
		const Maths::Vector2 vecSize = sizes[m_iIndex] * scale;;

		if (m_pTexture->GetAlpha())
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;

			AlphaBlend(hdc,
				(UINT)pos.x , (UINT)pos.y,
				(UINT)(vecSize.x), (UINT)(vecSize.y),
				imgHdc,
				(UINT)sprite.leftTop.x, (UINT)sprite.leftTop.y,
				(UINT)sizes[m_iIndex].x, (UINT)sizes[m_iIndex].y,
				func);
		}
		else
		{
			TransparentBlt(hdc,
				(UINT)pos.x, (UINT)pos.y,
				(UINT)(vecSize.x), (UINT)(vecSize.y),
				imgHdc,
				(UINT)sprite.leftTop.x, (UINT)sprite.leftTop.y,
				(UINT)sizes[m_iIndex].x, (UINT)sizes[m_iIndex].y,
				RGB(255, 0, 255));
		}
	}

	void  CAnimation::RenderPNG(HDC hdc, float rot,const Maths::Vector2& pos, const Maths::Vector2& scale, const Sprite& sprite) const
	{
		//Gdiplus::ImageAttributes imgAtt = {};
		//imgAtt.SetColorKey(Gdiplus::Color(100, 100, 100), Gdiplus::Color(255, 255, 255));

		Gdiplus::Graphics graphics(hdc);

		graphics.TranslateTransform(pos.x, pos.y);
		graphics.RotateTransform(rot);
		graphics.TranslateTransform(-pos.x, -pos.y);

		const auto& sizes = m_pTexture->GetSpriteSize();
		const Maths::Vector2 vecSize = sizes[m_iIndex] * scale;

		Gdiplus::Rect rect = Gdiplus::Rect(
			(UINT)(pos.x - (vecSize.x * 0.5f)),
			(UINT)(pos.y - (vecSize.y * 0.5f)),
			(UINT)vecSize.x,
			(UINT)vecSize.y);

		graphics.DrawImage(m_pTexture->GetImage(),
			rect,
			(UINT)sprite.leftTop.x, 
			(UINT)sprite.leftTop.y,
			(UINT)vecSize.x, 
			(UINT)vecSize.y,
			Gdiplus::UnitPixel,
			nullptr);
	}

	void  CAnimation::CreateAnimation(const std::wstring& name, CTexture* spriteSheet, Vector2 leftTop, 
		/*Vector2 size, Vector2 offset,*/ UINT spriteLength, float duration)
	{
		m_pTexture = spriteSheet;
		m_fDuration = duration;
		if (m_pTexture->GetCount() < spriteLength)
		{	assert(true);	}

		SetName(name);
		const auto& sizes = m_pTexture->GetSpriteSize();
		const bool isCreate = m_pTexture->OnCreate();
		//const Maths::Vector2& offset = m_pTexture->GetOffset();
		m_vecSprites.reserve(spriteLength);

		float stackWidth = 0;
		for (UINT i = 0; i < spriteLength; i++)
		{
			Sprite sprite	= {};
			if (isCreate)
			{
				sprite.leftTop = Vector2(stackWidth , leftTop.y);
				stackWidth += sizes[i].x;
			}
			else
			{
				sprite.leftTop = Vector2(leftTop.x + (sizes[i].x * i), leftTop.y);
			}
			m_vecSprites.push_back(sprite);
		}

	}

}

