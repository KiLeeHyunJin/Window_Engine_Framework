#include "CPlayerCharacterActor.h"
#include "CRenderManager.h"
#include "CInputManager.h"

#include "CRigidbodyComponent.h"
#include "CBoxColliderComponent.h"

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

		m_pRigid = AddComponent<CRigidbodyComponent>();
		m_pBoxColl = AddComponent<CBoxColliderComponent>();
		
		m_pBoxColl->SetSize(Maths::Vector2(40, 70));
		//pBoxColl->SetAngle(20);
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
		const Maths::Vector2& velocity = m_pRigid->GetVelocity();

		if (velocity.y < 0)
		{
			m_pBoxColl->RemoveCollisionFlag((UINT)eLayer::Tile);
		}
		else
		{
			m_pBoxColl->AddCollisionFlag((UINT)eLayer::Tile);
		}

		return state;
	}

	void CPlayerCharacterActor::FixedTick()
	{
		SUPER::FixedTick();

		if (m_vecTiles.size() == 0)
			return;

		bool state = false;
		for (auto tile : m_vecTiles)
		{
			if (state == false && tile->TileAdjustPosition(m_pBoxColl))
			{
				state = true;
			}
		}
		m_pRigid->SetGround(state);
	}
	void CPlayerCharacterActor::OnCollisionEnter(CColliderComponent* other)
	{
		CTileActor* pTile = dynamic_cast<CTileActor*>(other->GetOwner());
		if(pTile != nullptr)
		{
			m_vecTiles.push_back(pTile);
		}
	}

	void CPlayerCharacterActor::OnCollisionStay(CColliderComponent* other)
	{
	}

	void CPlayerCharacterActor::OnCollisionExit(CColliderComponent* other)
	{
		CTileActor* pTile = dynamic_cast<CTileActor*>(other->GetOwner());
		if (pTile != nullptr)
		{
			auto iter = std::remove(m_vecTiles.begin(), m_vecTiles.end(), pTile);
			m_vecTiles.erase(iter);
		}
	}

	bool CPlayerCharacterActor::Render(HDC hdc) const
	{
		if (SUPER::Render(hdc) == false)
		{		return false;	}

		return true;
	}

}