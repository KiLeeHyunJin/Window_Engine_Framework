#include "CRigidbodyComponent.h"
#include "CTransformComponent.h"
#include "CGameObject.h"

#include "CTimeManager.h"

namespace Framework
{
	CRigidbodyComponent::CRigidbodyComponent() :
		CComponent(Enums::eComponentType::Rigidbody),
		m_fFriction(10.0f), m_fMass(1), m_bGround(false),
		m_vecAccelation		(Maths::Vector2::Zero),			m_vecForce			(Maths::Vector2::Zero),
		m_vecGravity		(Maths::Vector2(0,980)),		m_vecVelocity		(Maths::Vector2::Zero),
		m_vecLimitVelocity	(Maths::Vector2(1000,1000)),	m_vecLimitGravity	(Maths::Vector2(1000,1000))
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
		VelocityCompute();
		
		LimitSpeedCompute();

		if (m_vecVelocity.HasValue()) //���ӵ��� �ִٸ�
		{
			ChangePosition();
		}
	}
	void CRigidbodyComponent::LastTick()
	{
	}
	void CRigidbodyComponent::Render(HDC hdc)
	{
	}
	
	void CRigidbodyComponent::VelocityCompute()
	{
		if (m_vecForce.HasValue())
		{
			m_vecAccelation = m_vecForce / m_fMass; //���ӵ� = �� / ����
			m_vecVelocity += m_vecAccelation * TIME::DeltaTime(); //�����Ӵ� ���ӵ��� ����ؼ� �ӵ��� �ջ�
		}
		else
		{
			if (m_vecAccelation.HasValue())
			{
				m_vecAccelation.Clear();
			}
		}
	}

	void CRigidbodyComponent::LimitSpeedCompute()
	{
		const Maths::Vector2 gravityDir = m_vecGravity.Normalized();

		if (gravityDir.HasValue() == false && 
			m_vecVelocity.HasValue() == false)
		{
			return;
		}

		if (m_bGround)
		{
			float dot = Maths::Vector2::Dot(m_vecVelocity, gravityDir);
			m_vecVelocity -= gravityDir * dot;
		}
		else
		{
			m_vecVelocity += m_vecGravity * TIME::DeltaTime();
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
	}

	void CRigidbodyComponent::ChangePosition()
	{
		const float tickTime = TIME::DeltaTime();

		Maths::Vector2 friction = m_vecVelocity.Normalized() * -1; //������ ����
		friction = friction * (m_fFriction * m_fMass * tickTime); //������ ���

		if (m_vecVelocity.TotalElementSize() <= friction.TotalElementSize()) //�ӵ��� �����º��� �۰ų� ũ�� ����
		{
			m_vecVelocity.Clear();
			return;
		}

		m_vecVelocity += friction; //�ӵ��� ������ �ջ��Ͽ� �ӵ� ����

		CTransformComponent* pTr = GetOwner()->GetTransformComponent();
		Maths::Vector2 pos = pTr->GetPos();
		pos += m_vecVelocity * tickTime;
		pTr->SetPos(pos); //���� ��ġ���� �̵� �������� �̵�

		if (m_vecForce.HasValue())
		{
			m_vecForce.Clear();
		}
	}
}