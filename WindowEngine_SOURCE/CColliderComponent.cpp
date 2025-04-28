#include "CColliderComponent.h"
#include "CBoxColliderComponent.h"
#include "CLineComponent.h"
#include "CRigidbodyComponent.h"

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
		if (m_pTriggerEvent != nullptr)
		{
			m_pTriggerEvent->first -= GET_SINGLE(TIME).DeltaTime();
			if (m_pTriggerEvent->first <= 0)
			{
				m_bTrigger = m_pTriggerEvent->second;
				delete m_pTriggerEvent;
				m_pTriggerEvent = nullptr;
			}
		}
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

	void CColliderComponent::EventTrigger(float waitTime, bool state)
	{
		if (m_pTriggerEvent != nullptr)
		{
			if (m_pTriggerEvent->first < waitTime)
			{
				return;
			}
		}
		m_pTriggerEvent = new  std::pair<FLOAT, BOOL>(waitTime, state);
	}

	const bool CColliderComponent::CheckCollisionBoxToBox(CColliderComponent* box1, CColliderComponent* box2)
	{
		const INT box1Angle = (INT)box1->GetAngle();
		const INT box2Angle = (INT)box2->GetAngle();

		const CBoxColliderComponent* boxColl1 = dynamic_cast<CBoxColliderComponent*>(box1);
		const CBoxColliderComponent* boxColl2 = dynamic_cast<CBoxColliderComponent*>(box2);
		if ((box1Angle % 180) == 0 && (box2Angle % 180) == 0) //AABB 충돌
		{
			///AABB 충돌
			RECT box1Rect = boxColl1->GetRect();
			RECT box2Rect = boxColl2->GetRect();
			RECT rect;
			return ::IntersectRect(&rect, &box1Rect, &box2Rect);
		}

		///OBB 충돌
		{
			const Maths::Vector2& box1OriginPos = box1->GetOwner()->GetPosition();
			const Maths::Vector2& box2OriginPos = box2->GetOwner()->GetPosition();

			const Maths::Vector2& box1OriginOffset = box1->GetOffset();
			const Maths::Vector2& box2OriginOffset = box2->GetOffset();

			const Maths::Vector2& box1Size = box1->GetSize();
			const Maths::Vector2& box2Size = box2->GetSize();

			Maths::Vector2 box1Pos = box1OriginPos + box1OriginOffset;
			Maths::Vector2 box2Pos = box2OriginPos + box2OriginOffset;

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
		//if (target->GetTrigger() || other->GetTrigger())
		//{
		//	return;
		//} 
		CActor* pTarget = target->GetOwner();
		CRigidbodyComponent* pRigid = pTarget->GetComponent<CRigidbodyComponent>();
		if (pRigid != nullptr)
		{
			pRigid->AdjustPosition(pTarget->GetComponent<CBoxColliderComponent>(), other->GetOwner()->GetComponent<CBoxColliderComponent>());
		}
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