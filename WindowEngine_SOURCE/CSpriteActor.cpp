#include "CSpriteActor.h"
#include "Utils.h"


namespace Framework
{
	CSpriteActor::CSpriteActor(UINT layer) : CActor(layer), m_pSprite(nullptr)
	{
	}
	CSpriteActor::~CSpriteActor()
	{
	}
	void CSpriteActor::BeginPlay()
	{
		SUPER::BeginPlay();
	}
	void CSpriteActor::Release()
	{
		SUPER::Release();

	}
	bool CSpriteActor::Tick()
	{
		return SUPER::Tick();
	}
	bool CSpriteActor::LastTick()
	{
		return SUPER::LastTick();
	}
	void CSpriteActor::Render(HDC hdc) const
	{
		SUPER::Render(hdc);
		if (m_pSprite == nullptr)
		{
			return;
		}
		const Maths::Vector2& position = GetPosition();
		const Maths::Vector2Int& spriteSize = m_pSprite->GetSize();
		const Maths::Vector2Int& spriteLeftTop = m_pSprite->GetLeftTop();
		HDC spriteHdc = m_pSprite->GetHDC();

		Utils::UtilBitBlt(hdc, position, spriteSize, m_pSprite);
		//BitBlt(hdc, position.x, position.y, spriteSize.x, spriteSize.y, spriteHdc, spriteLeftTop.x, spriteLeftTop.y, SRCCOPY);
	}
	void CSpriteActor::FixedTick()
	{
	}
}
