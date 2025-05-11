#include "CItemActor.h"
#include "..//WindowEngine_SOURCE//CTimeManager.h"
#include "..//WindowEngine_SOURCE//CRigidbodyComponent.h"
#include "..//WindowEngine_SOURCE//CBoxColliderComponent.h"
#include "CTileCollisionComponent.h"
#include "CTileActor.h"
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

		m_pRigid	= AddComponent<CRigidbodyComponent>();
		m_pBoxColl	= AddComponent<CBoxColliderComponent>();
		m_pTileColl = AddComponent<CTileCollisionComponent>();

		m_pBoxColl->SetTrigger(false);
		m_pBoxColl->SetSize(Maths::Vector2(20,20));
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
			if (m_fRot > 180)
			{
				m_fRot = m_fRot - 180;
				m_shrtRotCount++;
				if (m_shrtRotCount == 5)
				{
					m_bstandBy = true;
					m_bUp = true;
					m_fRot = 0;
				}
			}
		}

		if (m_bstandBy)
		{
			float yPos;
			Maths::Vector2 local = GetLocalPosition();
			if (m_bUp)
			{
				yPos = GET_SINGLE(TIME).DeltaTime() * 20 * -1;
				m_fYPos += yPos;
				if (m_fYPos < m_fRecordY - 15)
				{
					m_bUp = false;
				}
			}
			else
			{
				yPos = GET_SINGLE(TIME).DeltaTime() * 20;
				m_fYPos += yPos;
				if (m_fYPos > m_fRecordY)
				{
					m_bUp = true;
				}
			}
			local.y += yPos;
			SetLocalPosition(local);
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

	void CItemActor::OnCollisionEnter(CColliderComponent* other)
	{
		CTileActor* pTile = dynamic_cast<CTileActor*>(other->GetOwner());
		if (pTile != nullptr)
		{
			m_pTileColl->AddTile(pTile);
			m_pRigid->SetFreeze(true);
			m_pBoxColl->SetTrigger(true);
			m_fRecordY = GetLocalPosition().y;
		}
	}


	void CItemActor::OnCollisionExit(CColliderComponent* other)
	{
		CTileActor* pTile = dynamic_cast<CTileActor*>(other->GetOwner());
		if (pTile != nullptr)
		{
			m_pTileColl->RemoveTile(pTile);
		}
	}
}