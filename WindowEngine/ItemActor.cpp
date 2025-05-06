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
		SUPER::Initialize();

		m_pRigid = AddComponent<CRigidbodyComponent>();
		m_pBoxColl = AddComponent<CBoxColliderComponent>();
		m_pTileColl = AddComponent<CTileCollisionComponent>();
	}
	void ItemActor::BeginPlay()
	{
		SUPER::BeginPlay();
	}
	void ItemActor::Release()
	{
		SUPER::Release();
	}
	bool ItemActor::Tick()
	{
		bool state = SUPER::Tick();
		return state;
	}
	bool ItemActor::LastTick()
	{
		bool state = SUPER::LastTick();
		return state;
	}
	void ItemActor::FixedTick()
	{
		SUPER::FixedTick();
	}
	bool ItemActor::Render(HDC hdc) const
	{
		if (SUPER::Render(hdc) == false)
		{
			return false;
		}
		return false;
	}
}