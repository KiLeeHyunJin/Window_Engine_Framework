#include "CAnimation.h"

#include "CActor.h"
#include "CRenderer.h"

#include "CTransformComponent.h"
#include "CAnimatorComponent.h"
#include "CCameraComponent.h"
#include "CResourceManager.h"

#include "CTimeManager.h"
#include "CInputManager.h"
#include "CSprite.h"


namespace Framework
{

	 CAnimation::CAnimation() :
		CResource(Enums::eResourceType::Animation),
		m_pOwner(nullptr), m_vecSprites{},
		m_iIndex(-1), m_fTime(0), m_bCompleted(false), m_bLoop(false)
	{
		RenderFunc[(int)CTexture::eTextureType::Bmp] = &CAnimation::RenderBMP;
		RenderFunc[(int)CTexture::eTextureType::Png] = &CAnimation::RenderPNG;

	}

	 CAnimation::~CAnimation()
	{
	}

	 void CAnimation::CreateAnimation(const std::wstring& name, bool loop)
	 {
		 SetName(name);
		 m_bLoop = loop;
	 }

	void  CAnimation::Reset()
	{
		m_fTime = 0.0f;
		m_iIndex = 0;
		m_bCompleted = false;
	}

	void  CAnimation::TickComponent()
	{
		if (m_bCompleted)
		{
			return;
		}
		if (m_vecSprites.size() == 0)
		{
			return;
		}

		m_fTime += GET_SINGLE(TIME).DELTATIME;
		const float duration = m_vecSprites[m_iIndex].second;
		if (duration < m_fTime)
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
		if (m_vecSprites.size() == 0)
		{	return;	 }

		const CActor* pObj = m_pOwner->GetOwner();
		Vector2 pos = pObj->GetPosition();


		const CCameraComponent* mainCam = Renderer::CRenderer::GetMainCamera();
		if (mainCam != nullptr)
		{	pos = mainCam->CaluatePosition(pos);	}

		const Resource::CSprite* sprite = m_vecSprites[m_iIndex].first;
		const int idx = (int)sprite->GetTextureType();

		const Vector2& scale = pObj->GetScale();
		const float rot = pObj->GetRotate();

		(this->*RenderFunc[idx])(hdc, rot, pos, scale);

	}



	void  CAnimation::RenderBMP(HDC hdc, float rot, const Maths::Vector2& pos, const Maths::Vector2& scale) const
	{
		//const auto& sizes = 0;//m_pTexture->GetSpriteSize();
		const Resource::CSprite* sprite = m_vecSprites[m_iIndex].first;
		HDC imgHdc = sprite->GetHDC();

		const Maths::Vector2Int& leftTop = sprite->GetLeftTop();
		const Maths::Vector2Int& spriteSize = sprite->GetSize();
		const Maths::Vector2 vecSize = spriteSize * scale;// (scale.x * spriteSize.x, scale.y * spriteSize.y);

		if (sprite->GetAlpha())
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
				(UINT)leftTop.x, (UINT)leftTop.y,
				(UINT)spriteSize.x, (UINT)spriteSize.y,
				func);
		}
		else
		{
			TransparentBlt(hdc,
				(UINT)pos.x, (UINT)pos.y,
				(UINT)(vecSize.x), (UINT)(vecSize.y),
				imgHdc,
				(UINT)leftTop.x, (UINT)leftTop.y,
				(UINT)spriteSize.x, (UINT)spriteSize.y,
				RGB(255, 0, 255));
		}
	}

	void  CAnimation::RenderPNG(HDC hdc, float rot,const Maths::Vector2& pos, const Maths::Vector2& scale) const
	{
		//Gdiplus::ImageAttributes imgAtt = {};
		//imgAtt.SetColorKey(Gdiplus::Color(100, 100, 100), Gdiplus::Color(255, 255, 255));

		Gdiplus::Graphics graphics(hdc);

		graphics.TranslateTransform(pos.x, pos.y);
		graphics.RotateTransform(rot);
		graphics.TranslateTransform(-pos.x, -pos.y);

		const Resource::CSprite* sprite = m_vecSprites[m_iIndex].first;
		HDC imgHdc = sprite->GetHDC();

		const Maths::Vector2Int& leftTop = sprite->GetLeftTop();
		const Maths::Vector2Int& spriteSize = sprite->GetSize();
		const Maths::Vector2 vecSize = scale * spriteSize;

		Gdiplus::Rect rect = Gdiplus::Rect(
			(UINT)(pos.x - (vecSize.x * 0.5f)),
			(UINT)(pos.y - (vecSize.y * 0.5f)),
			(UINT)vecSize.x,
			(UINT)vecSize.y);

		graphics.DrawImage(sprite->GetImage(),
			rect,
			(UINT)leftTop.x,
			(UINT)leftTop.y,
			(UINT)vecSize.x, 
			(UINT)vecSize.y,
			Gdiplus::UnitPixel,
			nullptr);
	}

	//void  CAnimation::CreateAnimation(const std::wstring& name, bool loop)
	//{
	//	m_pTexture = const_cast<CTexture*>(spriteSheet);
	//	m_fDuration = duration;
	//	if (m_pTexture->GetCount() < spriteLength)
	//	{	assert(true);	}

	//	SetName(name);
	//	const auto& sizes = m_pTexture->GetSpriteSize();
	//	const bool isCreate = m_pTexture->OnCreate();
	//	m_vecSprites.reserve(spriteLength);

	//	float stackWidth = 0;
	//	for (UINT i = 0; i < spriteLength; i++)
	//	{
	//		Maths::Vector2 vec	= {};
	//		if (isCreate)
	//		{
	//			vec = Vector2(stackWidth , leftTop.y);
	//		}
	//		else
	//		{
	//			vec = Vector2(leftTop.x + stackWidth, leftTop.y);
	//		}
	//		stackWidth += sizes[i].x;

	//		m_vecVectors.push_back(vec);
	//	}

	//}

}

