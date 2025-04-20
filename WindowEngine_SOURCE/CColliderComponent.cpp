#include "CColliderComponent.h"
#include "CBoxColliderComponent.h"
#include "CLineComponent.h"

namespace Framework
{
	UINT32 CColliderComponent::m_collId = 1;


	CColliderComponent::CColliderComponent(eColliderType colliderType):
		CComponent(Enums::eComponentType::Collider), m_iColliderId(m_collId++),
		m_vecSize(Maths::Vector2::One), m_eColliderType(colliderType), m_bTrigger(false), m_iCollisionFlag(UINT32_MAX), m_fAngle(0)
	{
	}

	CColliderComponent::~CColliderComponent()
	{
	}
	void CColliderComponent::BeginPlay()
	{
	}
	void CColliderComponent::Release()
	{
	}
	bool CColliderComponent::TickComponent()
	{
		return true;
	}
	bool CColliderComponent::LastTickComponent()
	{
		return true;
	}

	void CColliderComponent::Render(HDC hdc)
	{
	}

	/// <summary>
	/// 순수가상함수 
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	const bool CColliderComponent::CheckCollision(CColliderComponent* other)
	{
		return CheckFlag(this, other);
	}

	const bool CColliderComponent::CheckCollisionBoxToBox(CColliderComponent* box1, CColliderComponent* box2)
	{
		const Maths::Vector2& box1OriginPos = box1->GetOwner()->GetPosition();
		const Maths::Vector2& box2OriginPos = box2->GetOwner()->GetPosition();

		const Maths::Vector2& box1OriginOffset = box1->GetOffset();
		const Maths::Vector2& box2OriginOffset = box2->GetOffset();

		const Maths::Vector2& box1Size = box1->GetSize();
		const Maths::Vector2& box2Size = box2->GetSize();

		Maths::Vector2 box1Pos = box1OriginPos + box1OriginOffset;
		Maths::Vector2 box2Pos = box2OriginPos + box2OriginOffset;

		const INT box1Angle = (INT)box1->GetAngle();
		const INT box2Angle = (INT)box2->GetAngle();

		if ((box1Angle % 180) == 0 && (box2Angle % 180) == 0)
		{
			///AABB 충돌
			if (Maths::Abs(box1Pos.x - box2Pos.x) <= (box1Size.x + box2Size.x) * 0.5f &&
				Maths::Abs(box1Pos.y - box2Pos.y) <= (box1Size.y + box2Size.y) * 0.5f)
			{
				return true;
			}
			return false;
		}
		else
		{
			///OBB 충돌
			const CBoxColliderComponent* boxColl1 = dynamic_cast<CBoxColliderComponent*>(box1);
			const CBoxColliderComponent* boxColl2 = dynamic_cast<CBoxColliderComponent*>(box2);
			
			//모서리를 가져온다.
			const std::vector<Maths::Vector2>& boxColl1Points = boxColl1->GetPoints();
			const std::vector<Maths::Vector2>& boxColl2Points = boxColl2->GetPoints();

			std::vector<Maths::Vector2> box1Points;
			std::vector<Maths::Vector2> box2Points;
			box1Points.reserve(4);
			box2Points.reserve(4);

			for (auto& point : boxColl1Points)
			{
				box1Points.push_back(Maths::Vector2(point + box1Pos));
			}
			for (auto& point : boxColl2Points)
			{
				box2Points.push_back(Maths::Vector2(point + box2Pos));
			}

			//축을 가져온다.
			const std::vector<Maths::Vector2>& boxColl1Axis = boxColl1->GetAxis();
			const std::vector<Maths::Vector2>& boxColl2Axis = boxColl2->GetAxis();

			for (const Maths::Vector2& axis : boxColl1Axis)  //box1의 축을 기준으로 겹치는지 확인
			{
				if (ProjectionCollisionCheck(box1Points, box2Points, axis))
				{
					return false;
				}
			}
			for (const Maths::Vector2& axis : boxColl2Axis)  //box2의 축을 기준으로 겹치는지 확인
			{ //obb2의 2변의 방향
				if (ProjectionCollisionCheck(box1Points, box2Points, axis))
				{
					return false;
				}
			}
			return true;
		}
	}

#pragma region NoUsed
	//const bool CColliderComponent::CheckCollisionBoxToCircle(CColliderComponent* owner, CColliderComponent* other)
	//{
	//	return false;
	//}

	//const bool CColliderComponent::CheckCollisionCircleToCircle(CColliderComponent* circle1, CColliderComponent* circle2)
	//{
	//	const Maths::Vector2& circle1OriginPos = circle1->GetOwner()->GetPosition();
	//	const Maths::Vector2& circle2OriginPos = circle2->GetOwner()->GetPosition();

	//	const Maths::Vector2& circle1OriginOffset = circle1->GetOffset();
	//	const Maths::Vector2& circle2OriginOffset = circle2->GetOffset();

	//	const Maths::Vector2& circle1Size = circle1->GetSize();// * 100;
	//	const Maths::Vector2& circle2Size = circle2->GetSize();// * 100;

	//	const Maths::Vector2 circle1Pos = circle1OriginPos + circle1OriginOffset;
	//	const Maths::Vector2 circle2Pos = circle2OriginPos + circle2OriginOffset;

	//	const float lenght = (circle1Pos - circle2Pos).Length();

	//	if (lenght <= (circle1Size.x + circle2Size.x) * 0.5f)
	//	{
	//		return true;
	//	}
	//	return false;
	//}
	//

#pragma endregion



	void CColliderComponent::AdjustPosition(CColliderComponent* target, CColliderComponent* other)
	{
		if (target->GetTrigger() || other->GetTrigger())
		{		return;				} //물리충돌이 필요한 대상인지 확인

		CBoxColliderComponent* targetCollider = dynamic_cast<CBoxColliderComponent*>(target);
		if (CheckCollisionLine(targetCollider, other))
		{
			return;
		}

		CBoxColliderComponent* otherCollider = dynamic_cast<CBoxColliderComponent*>(other);

		RECT targetRect = targetCollider->GetRect();
		RECT otherRect = otherCollider->GetRect();

		const CActor* targetOwner = target->GetOwner();

		const Maths::Vector2& pos = targetOwner->GetPosition();
		const Maths::Vector2& pre = targetOwner->GetPrevPosition();
		if (pos == pre)
			return;

		Maths::Vector2 moveSqrDir = targetOwner->GetMoveSqrDirection();
		if ((INT)targetCollider->GetAngle() % 180 != 0 || (INT)otherCollider->GetAngle() % 180 != 0)
		{
			//OBB
		}
		else
		{
			RECT collisionRect;
			if (!::IntersectRect(&collisionRect, &targetRect, &otherRect))
				return; // 충돌 없으면 종료

			if (moveSqrDir.x == moveSqrDir.y) //양방향 이동
			{
				DiagonalAdjustPosition(moveSqrDir, collisionRect, targetCollider, otherCollider);
			}
			else //단방향 이동
			{
				SimpleAdjustPosition(collisionRect, targetCollider, otherCollider);
			}
		}
	}

	bool CColliderComponent::CheckCollisionLine(CBoxColliderComponent* target, CColliderComponent* other)
	{
		CLineComponent* pLineComponent = other->GetOwner()->GetComponent<CLineComponent>();
		if (pLineComponent != nullptr)
		{
			CActor* targetOwner = target->GetOwner();
			const Maths::Vector2& pos = targetOwner->GetPosition() + target->GetOffset();
			float y;
			if (pLineComponent->GetPositionY(pos.x, &y))
			{
				const Maths::Vector2 halfSize = target->GetSize() * 0.5f;
				targetOwner->SetPosition(Maths::Vector2(pos.x, y - halfSize.y));
				return true;
			}
		}
		return false;
	}

	void CColliderComponent::DiagonalAdjustPosition(const Maths::Vector2& moveSqrDir, const RECT& collisionRect, CBoxColliderComponent* targetBoxCollider, CBoxColliderComponent* otherBoxCollider)
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


	void CColliderComponent::SimpleAdjustPosition(const RECT& collisionRect, CBoxColliderComponent* targetBoxCollider, CBoxColliderComponent* otherBoxCollider)
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

#pragma region  OBB
	void CColliderComponent::Projection(const std::vector<Maths::Vector2>& verts, const Maths::Vector2& axis, float& min, float& max)
	{
		min = max = Maths::Vector2::Dot(verts[0], axis); //정점과 변의 방향의 외적 , 0이면 수직
		for (const Maths::Vector2& v : verts) {
			float proj = Maths::Vector2::Dot(v, axis); //정점과 변의 방향 외적
			if (proj < min) min = proj;
			if (proj > max) max = proj;
		}
	}

	bool CColliderComponent::ProjectionCollisionCheck(
		const std::vector<Maths::Vector2>& verts1,
		const std::vector<Maths::Vector2>& verts2,
		const Maths::Vector2& axis)
	{
		float minA, maxA, minB, maxB;
		Projection(verts1, axis, minA, maxA); //obb 1번째 정점s,  변의 방향
		Projection(verts2, axis, minB, maxB);// obb 2번째 정점s, 변의 방향
		return maxA < minB || maxB < minA;
	}
#pragma endregion


	


}