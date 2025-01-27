#include "CRigidbodyComponent.h"
#include "CTransformComponent.h"
#include "CGameObject.h"

#include "CTimeManager.h"

namespace Framework
{
	CRigidbodyComponent::CRigidbodyComponent() :
		CComponent(Enums::eComponentType::Rigidbody),
		m_fFriction(20.0f), m_fMass(1.0f), m_bGround(false),
		m_vecAccelation(Maths::Vector2::Zero),		m_vecForce(Maths::Vector2::Zero),
		m_vecGravity(Maths::Vector2::Zero),			m_vecVelocity(Maths::Vector2::Zero),
		m_vecLimitVelocity(Maths::Vector2(100,10)),	m_vecLimitGravity(Maths::Vector2(100,100))
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

		if (m_vecForce.SqrLength() != 0.0f)
		{
			m_vecAccelation = m_vecForce / m_fMass; //가속도 = 힘 / 질량
			m_vecVelocity += m_vecAccelation * tickTime; //프레임당 가속도를 계산해서 속도에 합산
		}
		else
		{
			if (m_vecAccelation.x != 0.0f && 
				m_vecAccelation.y != 0.0f)
			{
				m_vecAccelation.Clear();
			}
		}
		
		const Maths::Vector2 gravityDir = m_vecGravity.Normalized();

		if (m_bGround)
		{
			float dot = Maths::Vector2::Dot(m_vecAccelation, gravityDir);
			m_vecVelocity -= gravityDir * dot;
		}
		else
		{
			m_vecVelocity += m_vecGravity * tickTime;
		}

		const float dot = Maths::Vector2::Dot(m_vecVelocity, gravityDir);

		Maths::Vector2 gravityDot = gravityDir * dot;
		Maths::Vector2 sideVelocity = m_vecVelocity - gravityDot;


		if (m_vecLimitGravity.y < gravityDot.Length())
		{
			gravityDot.Normalize();
			gravityDot *= m_vecLimitVelocity.y;
		}

		if (m_vecLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= m_vecLimitVelocity.x;
		}

		m_vecVelocity = gravityDot + sideVelocity;

		const float velocitySqrLen = m_vecVelocity.SqrLength();
		if (velocitySqrLen != 0.0f) //가속도가 있다면
		{
			Maths::Vector2 friction = -m_vecVelocity; //마찰력 방향
			friction = friction.Normalize() * m_fFriction * m_fMass * tickTime; //마찰력 계산

			if (m_vecVelocity.SqrLength() <= friction.SqrLength()) //속도가 마찰력보다 작거나 크면 정지
			{
				m_vecVelocity.Clear();
			}
			else
			{
				m_vecVelocity += friction; //속도에 마찰력 합산하여 속도 감소
			}

			CTransformComponent* pTr = GetOwner()->GetTransformComponent();
			Maths::Vector2 pos = pTr->GetPos();

			pos += m_vecVelocity * tickTime;
			pTr->SetPos(pos); //현재 위치에서 이동 방향으로 이동

			m_vecForce.Clear();
		}
	}
	void CRigidbodyComponent::LastTick()
	{
	}
	void CRigidbodyComponent::Render(HDC hdc)
	{

	}
}