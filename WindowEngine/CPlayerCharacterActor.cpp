#include "CPlayerCharacterActor.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CRigidbodyComponent.h"
#include "CBoxColliderComponent.h"
#include "ContentEnums.h"

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

		CRigidbodyComponent* pRigid = AddComponent<CRigidbodyComponent>();
		CBoxColliderComponent* pBoxColl = AddComponent<CBoxColliderComponent>();
		
		pBoxColl->SetSize(Maths::Vector2(40, 70));
		pBoxColl->SetAngle(20);
		pBoxColl->SetTrigger(false);
		pBoxColl->AddCollisionFlag((UINT)eLayer::Tile);
		pBoxColl->Initialize();

		pRigid->SetMass(60);
		pRigid->SetFriction(15);
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
		CRigidbodyComponent* pRigid = GetComponent<CRigidbodyComponent>();

		Maths::Vector2 addForceDir = {};

		const float yValue = pRigid->GetVelocity().y;

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
			if (pRigid->GetGround())
			{
				addForceDir += Maths::Vector2::Up * 400;
				pRigid->SetGround(false);
			}
		}

		if (addForceDir.HasValue())
		{
			if (addForceDir.y == 0)
			{
				addForceDir.y += yValue;
			}
			pRigid->SetVelocity(addForceDir);
		}

		bool state = SUPER::Tick();
		return state;
	}
	bool CPlayerCharacterActor::LastTick()
	{
		bool state = SUPER::LastTick();
		CRigidbodyComponent* pRigid = GetComponent<CRigidbodyComponent>();
		CColliderComponent* pColl = AddComponent<CBoxColliderComponent>();
		const Maths::Vector2& velocity = pRigid->GetVelocity();

		if (velocity.y < 0)
		{
			pColl->RemoveCollisionFlag((UINT)eLayer::Tile);
		}
		else
		{
			pColl->AddCollisionFlag((UINT)eLayer::Tile);
		}

		const bool tileCollision = m_iTileCollisionCount >= 1 ? true : false;
		if (tileCollision != pRigid->GetGround())
		{
			pRigid->SetGround(tileCollision);
		}
		return state;
	}
	void CPlayerCharacterActor::FixedTick()
	{
		SUPER::FixedTick();
	}
	bool CPlayerCharacterActor::Render(HDC hdc) const
	{
		if (SUPER::Render(hdc) == false)
		{		return false;	}

		return true;
	}

}