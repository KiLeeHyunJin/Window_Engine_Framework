#include "CRigidbodyComponent.h"
#include "CBoxColliderComponent.h"
#include "CLineComponent.h"

#include "CActor.h"

#include "CTimeManager.h"

namespace Framework
{
	CRigidbodyComponent::CRigidbodyComponent() :
		CComponent(Enums::eComponentType::Rigidbody),
		m_fFriction(10.0f), m_fMass(70), m_bGround(false),
		m_vecAccelation		(Maths::Vector2::Zero),			m_vecForce			(Maths::Vector2::Zero),
		m_vecGravity		(Maths::Vector2(0,980)),		m_vecVelocity		(Maths::Vector2::Zero),
		m_vecLimitVelocity	(Maths::Vector2(500, 600))//,		m_vecLimitGravity	(Maths::Vector2(500, 500))
	{
	}
	CRigidbodyComponent::~CRigidbodyComponent()
	{
	}


	bool CRigidbodyComponent::TickComponent()
	{
		if (m_bFreeze)
		{		return true;	}

		try
		{
			VelocityCompute();
			LimitSpeedCompute();

			if (m_vecVelocity.HasValue()) //가속도가 있다면
			{
				ChangePosition();
			}
			return true;

		}
		catch (std::exception e)
		{
			const std::string str = e.what();

		}

		return true;
	}
	
	void CRigidbodyComponent::FixedComponent()
	{
	}

	void CRigidbodyComponent::VelocityCompute()
	{

		if (m_vecForce.HasValue()) //힘을 가속도로 전환 후 폐기
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
			//if (m_vecVelocity.y != 0)
			{
				m_vecVelocity.y = m_vecGravity.y * GET_SINGLE(TIME).DeltaTime();
			}
			return;
		}
		//else
		{
			m_vecVelocity.y += m_vecGravity.y * GET_SINGLE(TIME).DeltaTime();

			m_vecVelocity.y = Maths::Clamp<FLOAT>(m_vecVelocity.y, m_vecLimitVelocity.y * -1, m_vecLimitVelocity.y);
			m_vecVelocity.x = Maths::Clamp<FLOAT>(m_vecVelocity.x, m_vecLimitVelocity.x * -1, m_vecLimitVelocity.x);

		}
	}

	void CRigidbodyComponent::ChangePosition()
	{
		if (m_vecVelocity.HasValue() == false)
		{
			return;
		}
		const float TickComponentTime = GET_SINGLE(TIME).DeltaTime();
		const float yValue = m_vecVelocity.y;
		//if (m_bGround)
		{
			Maths::Vector2 friction = m_vecVelocity.Normalized() * -1; //마찰력 방향
			friction = friction * (m_fFriction * m_fMass * TickComponentTime); //마찰력 계산

			if (m_vecVelocity.SqrLength() <= friction.SqrLength()) //속도가 마찰력보다 작거나 크면 정지
			{
				m_vecVelocity.Clear();
				return;
			}

			m_vecVelocity += friction; //속도에 마찰력 합산하여 속도 감소
		}
		m_vecVelocity.y = yValue;

		CActor* pActor = GetOwner();
		Maths::Vector2 pos = pActor->GetLocalPosition();
		pos = pos + (m_vecVelocity * TickComponentTime);
		pActor->SetLocalPosition(pos); //현재 위치에서 이동 방향으로 이동

		if (m_vecForce.HasValue()) //힘 폐기
		{
			m_vecForce.Clear();
		}
	}

	void CRigidbodyComponent::SetGround(bool isGround)
	{
		m_bGround = isGround;
	}

	void CRigidbodyComponent::AdjustPosition(CBoxColliderComponent* target, CBoxColliderComponent* other)
	{
		if (target->GetTrigger() || other->GetTrigger())
		{
			return;
		}//물리충돌이 필요한 대상인지 확인

		const CActor* targetOwner = target->GetOwner();

		const Maths::Vector2& pos = targetOwner->GetPosition();
		const Maths::Vector2& pre = targetOwner->GetPrevPosition();
		if (pos == pre)
		{		return;		}

		RECT collisionRect;
		{
			const RECT targetRect = target->GetRect();
			const RECT otherRect = target->GetRect();

			if (::IntersectRect(&collisionRect, &targetRect, &otherRect) == false)
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
		const CLineComponent* pLineComponent = other->GetOwner()->GetComponent<CLineComponent>();
		if (pLineComponent != nullptr)
		{
			if (pLineComponent->GetTrigger())
			{		return false;	}

			CActor* targetOwner = target->GetOwner();
			const Maths::Vector2 pos = targetOwner->GetPosition() + target->GetOffset();
			float lineYPos;
			if (pLineComponent->GetPositionY(pos.x, &lineYPos))
			{
				if (lineYPos > pos.y) //선보다 위
				{		return false;	}

				//선 높이랑 플레이어 높이가 플레이어의 콜라이더 박스 높이의 20% 보다 크다면 충돌 인정 X 
				if (Maths::Abs(lineYPos - pos.y) > (target->GetSize().y * 0.2f))
				{		return false;	}	

				targetOwner->SetLocalPosition(Maths::Vector2(pos.x, lineYPos));
				CRigidbodyComponent* pRigidbody = targetOwner->GetComponent<CRigidbodyComponent>();
				if (pRigidbody != nullptr)
				{		pRigidbody->SetGround(true);	}

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
		targetOwner->SetLocalPosition(resultPos);
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
		targetOwner->SetLocalPosition(currentPos + pushOffset);
	}
}