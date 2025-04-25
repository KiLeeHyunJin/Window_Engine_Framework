#include "CSpriteActor.h"



namespace Framework
{
	CSpriteActor::CSpriteActor(UINT layer) : CActor(layer), m_pSprite(nullptr)
	{
	}
	CSpriteActor::~CSpriteActor()
	{
	}


	void CSpriteActor::Initialize()
	{
		SUPER::Initialize();
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

	void CSpriteActor::FixedTick()
	{
		SUPER::FixedTick();
	}

	bool CSpriteActor::Render(HDC hdc) const
	{
		if (SUPER::Render(hdc) == false)
			return false;

		if (m_pSprite == nullptr)
		{
			return false;
		}
		const Maths::Vector2& position = GetPosition();
		const Maths::Vector2Int& spriteSize = m_pSprite->GetSize();
		const Maths::Vector2Int& spriteLeftTop = m_pSprite->GetLeftTop();

		Utils::UtilBitBlt(hdc, position, spriteSize, m_pSprite);

		return true;
		//BitBlt(hdc, position.x, position.y, spriteSize.x, spriteSize.y, spriteHdc, spriteLeftTop.x, spriteLeftTop.y, SRCCOPY);
	}

}
