#include "CColliderComponent.h"
#include "CActor.h"
#include "CCustomComponent.h"

namespace Framework
{
	UINT32 CColliderComponent::m_collId = 1;

	CColliderComponent::CColliderComponent():
		CComponent(Enums::eComponentType::Collider), m_eColliderType(eColliderType::None), m_iColliderId(m_collId++),
		m_vecSize(Maths::Vector2::One)
	{	
	}

	CColliderComponent::CColliderComponent(eColliderType colliderType):
		CComponent(Enums::eComponentType::Collider), m_iColliderId(m_collId++),
		m_vecSize(Maths::Vector2::One), m_eColliderType(colliderType)
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

	void CColliderComponent::OnCollisionEnter(CColliderComponent* other)
	{
		CCustomComponent* pCustom = GetOwner()->GetComponent<CCustomComponent>();
		pCustom->OnCollisionEnter(other);
	}

	void CColliderComponent::OnCollisionStay(CColliderComponent* other)
	{
		CCustomComponent* pCustom = GetOwner()->GetComponent<CCustomComponent>();
		pCustom->OnCollisionStay(other);
	}

	void CColliderComponent::OnCollisionExit(CColliderComponent* other)
	{
		CCustomComponent* pCustom = GetOwner()->GetComponent<CCustomComponent>();
		pCustom->OnCollisionExit(other);
	}

	/// <summary>
	/// 순수가상함수 
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool CColliderComponent::CheckCollision(CColliderComponent* other)
	{
		return false;
	}

	bool CColliderComponent::CheckCollisionBoxToBox(CColliderComponent* box1, CColliderComponent* box2)
	{
		const Maths::Vector2& box1OriginPos = box1->GetOwner()->GetPosition();
		const Maths::Vector2& box2OriginPos = box2->GetOwner()->GetPosition();

		const Maths::Vector2& box1OriginOffset = box1->GetOffset();
		const Maths::Vector2& box2OriginOffset = box2->GetOffset();

		const Maths::Vector2& box1Size = box1->GetSize();
		const Maths::Vector2& box2Size = box2->GetSize();

		const Maths::Vector2 box1Pos = box1OriginPos + box1OriginOffset;
		const Maths::Vector2 box2Pos = box2OriginPos + box2OriginOffset;

		if (Maths::Abs(box1Pos.x - box2Pos.x) < Maths::Abs((box1Size.x + box2Size.x) * 0.5f) &&
			Maths::Abs(box1Pos.y - box2Pos.y) < Maths::Abs((box1Size.y + box2Size.y) * 0.5f))
		{
			return true;
		}
		return false;
	}

	bool CColliderComponent::CheckCollisionBoxToCircle(CColliderComponent* owner, CColliderComponent* other)
	{
		return false;
	}
	bool CColliderComponent::CheckCollisionCircleToCircle(CColliderComponent* circle1, CColliderComponent* circle2)
	{
		const Maths::Vector2& circle1OriginPos = circle1->GetOwner()->GetPosition();
		const Maths::Vector2& circle2OriginPos = circle2->GetOwner()->GetPosition();

		const Maths::Vector2& circle1OriginOffset = circle1->GetOffset();
		const Maths::Vector2& circle2OriginOffset = circle2->GetOffset();

		const Maths::Vector2& circle1Size = circle1->GetSize();// * 100;
		const Maths::Vector2& circle2Size = circle2->GetSize();// * 100;

		const Maths::Vector2 circle1Pos = circle1OriginPos + circle1OriginOffset;
		const Maths::Vector2 circle2Pos = circle2OriginPos + circle2OriginOffset;


		//const Maths::Vector2 circle1CirclePos = circle1Pos + (circle1Size * 0.5f);
		//const Maths::Vector2 circle2CirclePos = circle2Pos + (circle2Size * 0.5f);

		const float lenght = (circle1Pos - circle2Pos).Length();

		if (lenght <= (circle1Size.x + circle2Size.x) * 0.5f)
		{
			return true;
		}
		return false;
	}
}