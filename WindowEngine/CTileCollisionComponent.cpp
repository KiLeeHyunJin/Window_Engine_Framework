#include "CTileCollisionComponent.h"

#include "CRigidbodyComponent.h"
#include "CBoxColliderComponent.h"
#include "CTileCollisionComponent.h"

#include "CTileActor.h"

#include "ContentEnums.h"

namespace Framework
{
	CTileCollisionComponent::CTileCollisionComponent()
	{
	}
	CTileCollisionComponent::~CTileCollisionComponent()
	{
	}
	void CTileCollisionComponent::BeginPlay()
	{
		CActor* pActor = GetOwner();
		m_pBoxColl	= pActor->GetComponent<CBoxColliderComponent>();
		m_pRigid	= pActor->GetComponent<CRigidbodyComponent>();

	}

	void CTileCollisionComponent::Release()
	{
	}

	bool CTileCollisionComponent::TickComponent()
	{
		return true;
	}

	bool CTileCollisionComponent::LastTickComponent()
	{
		const Maths::Vector2& velocity = m_pRigid->GetVelocity();

		if (velocity.y < 0)
		{
			m_pBoxColl->RemoveCollisionFlag((UINT)eLayer::Tile);
		}
		else
		{
			m_pBoxColl->AddCollisionFlag((UINT)eLayer::Tile);
		}
		return true;
	}

	void CTileCollisionComponent::FixedComponent()
	{
		bool state = false;
		if (m_pBoxColl->CheckCollisionFlag((UINT)eLayer::Tile) == false)
		{
			m_pRigid->SetGround(state);
			return;
		}

		if (m_vecTiles.empty() == false)
		{
			float tileY = 0;
			for (auto tile : m_vecTiles)
			{
				float newTileY = 0;
				if (tile->CheckCollisionLine(m_pBoxColl, newTileY))
				{
					if (tileY < newTileY)
					{
						if (state == false)
						{
							state = true;
						}
						tileY = newTileY;
					}
				}
			}
			if (state)
			{
				tileY += 0.05f;
				CActor* pActor = GetOwner();
				const Maths::Vector2& pos = pActor->GetLocalPosition();
				pActor->SetLocalPosition(Maths::Vector2(pos.x, tileY));
			}
		}
		m_pRigid->SetGround(state);
	}

	void CTileCollisionComponent::Render(HDC hdc)
	{
	}

}
