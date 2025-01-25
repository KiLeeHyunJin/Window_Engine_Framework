#include "CRigidbodyComponent.h"
#include "CTransformComponent.h"
#include "CGameObject.h"

#include "CTimeManager.h"

namespace Framework
{
	CRigidbodyComponent::CRigidbodyComponent() :
		CComponent(Enums::eComponentType::Rigidbody),
		m_fFriction(10.0f), m_fMass(1.0f),
		m_vecAccelation(Maths::Vector2::Zero), m_vecForce(Maths::Vector2::Zero),
		m_vecGravity(Maths::Vector2::Zero), m_vecVelocity(Maths::Vector2::Zero)
	{
	}
	CRigidbodyComponent::~CRigidbodyComponent()
	{
	}
	void CRigidbodyComponent::Initialize()
	{
	}
	void CRigidbodyComponent::Release()
	{
	}
	void CRigidbodyComponent::Tick()
	{
		const float tickTime = TIME::DeltaTime();

		m_vecAccelation = m_vecForce / m_fMass; //가속도 = 힘 / 질량
		m_vecVelocity += m_vecAccelation * tickTime;

		if (false == (m_vecAccelation == Maths::Vector2::Zero))
		{
			Maths::Vector2 friction = -m_vecVelocity;
			friction = friction.Normalize() * m_fFriction * m_fMass * tickTime;

			if (m_vecVelocity.SqrLength() <= friction.SqrLength())
			{
				m_vecVelocity = Maths::Vector2::Zero;
			}
			else
			{
				m_vecVelocity += friction;
			}
		}

		CTransformComponent* pTr = GetOwner()->GetTransformComponent();
		Maths::Vector2 pos = pTr->GetPos();
		pos += m_vecVelocity * tickTime;
		pTr->SetPos(pos);

		m_vecForce.Clear();

	}
	void CRigidbodyComponent::LastTick()
	{
	}
	void CRigidbodyComponent::Render(HDC hdc)
	{
	}
}