#include "CSpriteActor.h"



namespace Framework
{
	void SpriteActor::BeginPlay()
	{
		SUPER::BeginPlay();
	}
	void SpriteActor::Release()
	{
		SUPER::Release();

	}
	bool SpriteActor::Tick()
	{
		return SUPER::Tick();
	}
	bool SpriteActor::LastTick()
	{
		return LastTick();
	}
	void SpriteActor::Render(HDC hdc) const
	{
		SUPER::Render(hdc);
	}
}
