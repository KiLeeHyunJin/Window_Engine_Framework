#include "ItemActor.h"


namespace Framework
{
	ItemActor::ItemActor(INT layer) : CSpriteActor(layer)
	{
	}
	ItemActor::~ItemActor()
	{
	}
	void ItemActor::Initialize()
	{
	}
	void ItemActor::BeginPlay()
	{
	}
	void ItemActor::Release()
	{
	}
	bool ItemActor::Tick()
	{
		return false;
	}
	bool ItemActor::LastTick()
	{
		return false;
	}
	void ItemActor::FixedTick()
	{
	}
	bool ItemActor::Render(HDC hdc) const
	{
		return false;
	}
}