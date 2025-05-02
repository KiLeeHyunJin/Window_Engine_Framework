#include "CPlayerCharacterActor.h"
#include "CRenderManager.h"
#include "CInputManager.h"

#include "CRigidbodyComponent.h"
#include "CBoxColliderComponent.h"
#include "CTileCollisionComponent.h"

#include "ContentEnums.h"

#include "CTileActor.h"

namespace Framework
{
	CPlayerCharacterActor::CPlayerCharacterActor(UINT layer) : CFlipbookActor(layer)
	{
	}
	CPlayerCharacterActor::~CPlayerCharacterActor()
	{
	}
	void CPlayerCharacterActor::Initialize()
	{
		SUPER::Initialize();

		m_pRigid	= AddComponent<CRigidbodyComponent>();
		m_pBoxColl	= AddComponent<CBoxColliderComponent>();
		m_pTileColl = AddComponent<CTileCollisionComponent>();

		m_pBoxColl->SetSize(Maths::Vector2(40, 70));
		m_pBoxColl->SetTrigger(false);
		m_pBoxColl->AddCollisionFlag((UINT)eLayer::Tile);
		m_pBoxColl->Initialize();

		m_pRigid->SetMass(60);
		m_pRigid->SetFriction(15);
	}
	void CPlayerCharacterActor::BeginPlay()
	{
		SUPER::BeginPlay();
	}
	void CPlayerCharacterActor::Release()
	{
		SUPER::Release();
	}
	bool CPlayerCharacterActor::Tick()
	{
		Maths::Vector2 addForceDir = {};

		const float yValue = m_pRigid->GetVelocity().y;

		const float speed = 20;
		const float movePower = speed * 5;
		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::Left))
		{
			addForceDir += Maths::Vector2::Left;
		}
		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::Right))
		{
			addForceDir += Maths::Vector2::Right;
		}

		addForceDir.Normalize();
		addForceDir *= movePower;

		if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::Space))
		{
			if (m_pRigid->GetGround())
			{
				addForceDir += Maths::Vector2::Up * 400;
				m_pRigid->SetGround(false);
			}
		}

		if (addForceDir.HasValue())
		{
			if (addForceDir.y == 0)
			{
				addForceDir.y += yValue;
			}
			m_pRigid->SetVelocity(addForceDir);
		}

		bool state = SUPER::Tick();
		return state;
	}

	bool CPlayerCharacterActor::LastTick()
	{
		bool state = SUPER::LastTick();


		return state;
	}

	void CPlayerCharacterActor::FixedTick()
	{
		SUPER::FixedTick();
	}

	void CPlayerCharacterActor::OnCollisionEnter(CColliderComponent* other)
	{
		CTileActor* pTile = dynamic_cast<CTileActor*>(other->GetOwner());
		if(pTile != nullptr)
		{
			m_pTileColl->AddTile(pTile);
		}
	}


	void CPlayerCharacterActor::OnCollisionExit(CColliderComponent* other)
	{
		CTileActor* pTile = dynamic_cast<CTileActor*>(other->GetOwner());
		if (pTile != nullptr)
		{
			m_pTileColl->RemoveTile(pTile);
		}
	}


	bool CPlayerCharacterActor::Render(HDC hdc) const
	{
		if (SUPER::Render(hdc) == false)
		{		return false;	}

		return true;
	}

}