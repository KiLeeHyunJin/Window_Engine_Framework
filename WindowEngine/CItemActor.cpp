#include "CItemActor.h"
#include "..//WindowEngine_SOURCE//CTimeManager.h"
#include "..//WindowEngine_SOURCE//CRigidbodyComponent.h"
#include "..//WindowEngine_SOURCE//CBoxColliderComponent.h"
#include "CTileCollisionComponent.h"
namespace Framework
{
	CItemActor::CItemActor(INT layer) : CSpriteActor(layer)
	{
	}
	CItemActor::~CItemActor()
	{
	}
	void CItemActor::Initialize()
	{
		SUPER::Initialize();

		m_pRigid = AddComponent<CRigidbodyComponent>();
		m_pBoxColl = AddComponent<CBoxColliderComponent>();
		m_pTileColl = AddComponent<CTileCollisionComponent>();

		m_pBoxColl->Initialize();
	}
	void CItemActor::BeginPlay()
	{
		SUPER::BeginPlay();
		Maths::Vector2 vecPop = Maths::Vector2::Up * 500;
		m_pRigid->AddVelocity(vecPop);
	}
	void CItemActor::Release()
	{
		SUPER::Release();
	}
	bool CItemActor::Tick()
	{
		bool state = SUPER::Tick();
		if (m_bstandBy == false)
		{
			m_fRot += GET_SINGLE(TIME).DeltaTime() * 800;
			if (m_fRot > 360)
			{
				m_shrtRotCount++;
				if (m_shrtRotCount == 4)
				{
					m_bstandBy = true;
					m_fRot = 0;
				}
				else
				{
					m_fRot = m_fRot - 360;
				}
			}
		}

		if (m_bstandBy)
		{

		}
		return state;
	}
	bool CItemActor::LastTick()
	{
		bool state = SUPER::LastTick();
		return state;
	}
	void CItemActor::FixedTick()
	{
		SUPER::FixedTick();
	}

	bool CItemActor::Render(HDC hdc) const
	{
		if (SUPER::Render(hdc) == false)
		{
			return false;
		}


		const Maths::Vector2& pos = GetRenderPosition();
		Maths::Vector2 start	= { pos.x - 25, pos.y - 50 };
		Maths::Vector2 end		= { pos.x + 25, pos.y };
		GET_SINGLE(RENDER).FrameRect(start, end,1, m_fRot);

		return false;
	}
}