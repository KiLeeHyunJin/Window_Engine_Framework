#include "CRigidbodyComponent.h"
#include "CTransformComponent.h"
#include "CActor.h"

#include "CTimeManager.h"

namespace Framework
{
	CRigidbodyComponent::CRigidbodyComponent() :
		CComponent(Enums::eComponentType::Rigidbody),
		m_fFriction(10.0f), m_fMass(50), m_bGround(false),
		m_vecAccelation		(Maths::Vector2::Zero),			m_vecForce			(Maths::Vector2::Zero),
		m_vecGravity		(Maths::Vector2(0,980)),		m_vecVelocity		(Maths::Vector2::Zero),
		m_vecLimitVelocity	(Maths::Vector2(1000,1000)),	m_vecLimitGravity	(Maths::Vector2(1000,1000))
	{
	}
	CRigidbodyComponent::~CRigidbodyComponent()
	{
	}
	
	void CRigidbodyComponent::BeginPlay()
	{
	}
	
	void CRigidbodyComponent::Release()
	{
	}

	bool CRigidbodyComponent::TickComponent()
	{
		VelocityCompute();
		
		//LimitSpeedCompute();

		if (m_vecVelocity.HasValue()) //가속도가 있다면
		{
			ChangePosition();
		}
		return true;
	}
	bool CRigidbodyComponent::LastTickComponent()
	{
		return true;
	}
	void CRigidbodyComponent::Render(HDC hdc)
	{
		//const CTransformComponent* pTr = ;
		Maths::Vector2 pos = GetOwner()->GetPosition();
		CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
		if (pCam != nullptr)
		{
			pos = pCam->CaluatePosition(pos);
		}


		std::wstring pointStr = L"x : " + std::to_wstring((int)m_vecVelocity.x) + L", Y : " + std::to_wstring((int)m_vecVelocity.y);
		int lenPos = (int)wcsnlen_s(pointStr.c_str(), 50);
		TextOut(hdc, (UINT)(pos.x + 30), (UINT)(pos.y), pointStr.c_str(), lenPos);
	}
	
	void CRigidbodyComponent::VelocityCompute()
	{
		if (m_vecForce.HasValue())
		{
			m_vecAccelation = m_vecForce / m_fMass; //가속도 = 힘 / 질량
			m_vecVelocity += m_vecAccelation * GET_SINGLE(TIME).DeltaTime(); //프레임당 가속도를 계산해서 속도에 합산
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
			const float dot = Maths::Vector2::Dot(m_vecVelocity, gravityDir);
			Maths::Vector2 minusGravityDir = gravityDir * dot;
			m_vecVelocity -= minusGravityDir;
		}
		else
		{
			m_vecVelocity += m_vecGravity * GET_SINGLE(TIME).DeltaTime();
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
		if (m_vecVelocity.HasValue() == false)
		{
			return;
		}
		const float TickComponentTime = GET_SINGLE(TIME).DeltaTime();

		Maths::Vector2 friction = m_vecVelocity.Normalized() * -1; //마찰력 방향
		friction = friction * (m_fFriction * m_fMass * TickComponentTime); //마찰력 계산

		if (m_vecVelocity.SqrLength() <= friction.SqrLength()) //속도가 마찰력보다 작거나 크면 정지
		{
			m_vecVelocity.Clear();
			return;
		}

		m_vecVelocity += friction; //속도에 마찰력 합산하여 속도 감소

		//CTransformComponent* pTr = GetOwner()->GetTransformComponent();
		Maths::Vector2 pos = GetOwner()->GetPosition();
		pos = pos + (m_vecVelocity * TickComponentTime);
		GetOwner()->SetPosition(pos); //현재 위치에서 이동 방향으로 이동

		if (m_vecForce.HasValue())
		{
			m_vecForce.Clear();
		}
	}
}