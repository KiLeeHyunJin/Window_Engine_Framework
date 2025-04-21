#include "CRigidbodyComponent.h"
#include "CBoxColliderComponent.h"
#include "CLineComponent.h"

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

	void CRigidbodyComponent::AdjustPosition(CBoxColliderComponent* target, CBoxColliderComponent* other)
	{
		const CActor* targetOwner = target->GetOwner();

		const Maths::Vector2& pos = targetOwner->GetPosition();
		const Maths::Vector2& pre = targetOwner->GetPrevPosition();
		if (pos == pre)
		{		return;		}

		if (CheckCollisionLine(target, other))
		{		return;		}

		RECT collisionRect;
		{
			const RECT targetRect = target->GetRect();
			const RECT otherRect = target->GetRect();

			if (!::IntersectRect(&collisionRect, &targetRect, &otherRect))
			{
				return; // 충돌 없으면 종료
			}
		}

		Maths::Vector2 moveSqrDir = targetOwner->GetMoveSqrDirection();
		if ((INT)target->GetAngle() % 180 != 0 || (INT)other->GetAngle() % 180 != 0)
		{
			//OBB
			return;
		}
		else
		{
			if (moveSqrDir.x == moveSqrDir.y) //양방향 이동
			{
				DiagonalAdjustPosition(moveSqrDir, collisionRect, target, other);
			}
			else //단방향 이동
			{
				SimpleAdjustPosition(collisionRect, target, other);
			}
		}
	}

	bool CRigidbodyComponent::CheckCollisionLine(CBoxColliderComponent* target, CBoxColliderComponent* other)
	{
		CLineComponent* pLineComponent = other->GetOwner()->GetComponent<CLineComponent>();
		if (pLineComponent != nullptr)
		{
			CActor* targetOwner = target->GetOwner();
			const Maths::Vector2& pos = targetOwner->GetPosition() + target->GetOffset();
			float y;
			if (pLineComponent->GetPositionY(pos.x, &y))
			{
				float diff = y - pos.y; 
				if (diff <= 0) //선이 중심보다 위에서 부딪히고있다면 무시
				{
					return false;
				}
				const Maths::Vector2 halfSize = target->GetSize() * 0.5f;
				targetOwner->SetPosition(Maths::Vector2(pos.x, y - halfSize.y));
				return true;
			}
		}
		return false;
	}

	void CRigidbodyComponent::DiagonalAdjustPosition(const Maths::Vector2& moveSqrDir, const RECT& collisionRect, CBoxColliderComponent* targetBoxCollider, CBoxColliderComponent* otherBoxCollider)
	{
		RECT targetRect = targetBoxCollider->GetRect();
		RECT otherRect = otherBoxCollider->GetRect();

		CActor* targetOwner = targetBoxCollider->GetOwner();
		const Maths::Vector2& currentPos = targetOwner->GetPosition();
		Maths::Vector2 resultPos = currentPos;

		// 충돌 깊이 계산
		float overlapX = static_cast<float>(collisionRect.right - collisionRect.left);
		float overlapY = static_cast<float>(collisionRect.bottom - collisionRect.top);

		constexpr float REMAIN_RATIO = 0.1f;
		constexpr float MIN_OVERLAP = 0.2f;
		float pushRatio = 1.0f - REMAIN_RATIO;

		if (overlapX < MIN_OVERLAP && overlapY < MIN_OVERLAP)
			return; // 무시 가능한 충돌

		// 밀어낼 거리 계산 (완전히 밀지 않고 일부 남김)
		float deltaX = moveSqrDir.x * overlapX * pushRatio;
		float deltaY = moveSqrDir.y * overlapY * pushRatio;

		// 소수점 손실 방지 0보다 크면 소수점 올림 낮으면 내림
		int offsetX = static_cast<int>(deltaX > 0 ? ceil(deltaX) : floor(deltaX));
		int offsetY = static_cast<int>(deltaY > 0 ? ceil(deltaY) : floor(deltaY));

		// X축 테스트
		RECT testX = targetRect;
		OffsetRect(&testX, offsetX, 0);
		RECT dummy;
		if (!::IntersectRect(&dummy, &testX, &otherRect))
			resultPos.x += static_cast<float>(offsetX);

		// Y축 테스트
		RECT testY = targetRect;
		OffsetRect(&testY, 0, offsetY);
		if (!::IntersectRect(&dummy, &testY, &otherRect))
			resultPos.y += static_cast<float>(offsetY);

		// 최종 위치 반영
		targetOwner->SetPosition(resultPos);
	}


	void CRigidbodyComponent::SimpleAdjustPosition(const RECT& collisionRect, CBoxColliderComponent* targetBoxCollider, CBoxColliderComponent* otherBoxCollider)
	{
		CActor* targetOwner = targetBoxCollider->GetOwner();
		// 현재 위치
		const Maths::Vector2& currentPos = targetOwner->GetPosition();
		const Maths::Vector2& otherPos = otherBoxCollider->GetOwner()->GetPosition();

		// 충돌 깊이
		const float overlapX = static_cast<float>(collisionRect.right - collisionRect.left);
		const float overlapY = static_cast<float>(collisionRect.bottom - collisionRect.top);

		constexpr float REMAIN_RATIO = 2.f;
		constexpr float MIN_OVERLAP = 1.9f;
		//float pushRatio = 1.0f - REMAIN_RATIO;

		RECT otherRect = otherBoxCollider->GetRect();

		// 밀어낼 오프셋
		Maths::Vector2 pushOffset;

		if (overlapX < overlapY)
		{
			if (overlapX <= MIN_OVERLAP)
				return;

			if (collisionRect.left == otherRect.left) //오른쪽 충돌
			{
				pushOffset.x = (overlapX * -1) + REMAIN_RATIO;
			}
			else //왼쪽 충돌
			{
				pushOffset.x = overlapX - REMAIN_RATIO;
			}
		}
		else
		{
			if (overlapY <= MIN_OVERLAP)
				return;

			RECT otherRect = otherBoxCollider->GetRect();
			if (collisionRect.top == otherRect.top) //아래 충돌
			{
				pushOffset.y = (overlapY * -1) + REMAIN_RATIO;
			}
			else //위 충돌
			{
				pushOffset.y = overlapY - REMAIN_RATIO;
			}
		}

		// 위치 적용
		targetOwner->SetPosition(currentPos + pushOffset);
	}
}