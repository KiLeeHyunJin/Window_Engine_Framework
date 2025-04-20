#include "CLineComponent.h"
#include "CBoxColliderComponent.h"

namespace Framework
{
	CLineComponent::CLineComponent() : CComponent(Enums::eComponentType::Line)
	{
	}
	CLineComponent::~CLineComponent()
	{
	}
	const Enums::eComponentType CLineComponent::GetComponentType() const
	{
		return Enums::eComponentType::Line;
	}
	void CLineComponent::BeginPlay()
	{
	
		
	}
	void CLineComponent::Release()
	{
	}
	void CLineComponent::Initialize()
	{
		CActor* owner = GetOwner();

		const CBoxColliderComponent* pCollider = owner->GetComponent<CBoxColliderComponent>();
		const Maths::Vector2& position = owner->GetPosition();
		const Maths::Vector2& offset = pCollider->GetOffset();
		const Maths::Vector2 halfSize = pCollider->GetSize() * 0.5f;


		const std::vector<Maths::Vector2>& axis = pCollider->GetAxis();

		const Maths::Vector2 axeX = axis[0] * halfSize.x;
		const Maths::Vector2 axeY = axis[1] * halfSize.y;

		const Maths::Vector2 pos = Maths::Vector2(position.x, position.y * 1.1f) + offset;

		const Maths::Vector2 left	( -axeX -axeY + pos);
		const Maths::Vector2 right	( axeX  -axeY + pos);


		m_vecStartPos	= left;
		m_vecEndPos		= right;
	}
	bool CLineComponent::TickComponent()
	{
		return false;
	}
	bool CLineComponent::LastTickComponent()
	{
		return false;
	}

	bool CLineComponent::CheckCollisionX(float x) const
	{
		if (x >= m_vecStartPos.x && x <= m_vecEndPos.x)
		{
			return true;
		}
		return false;
	}

	bool CLineComponent::GetPositionY(float x, float* y) const
	{
		if (CheckCollisionX(x) == false)
		{
			return false;
		}
		// 두 점을 지나는 직선의 방정식
		// Y - y1 = ((y2 - y1) / (x2 - x1)) * (X - x1)
		// Y  = ((y2 - y1) / (x2 - x1)) * (X - x1) + y1
		const float startX = m_vecStartPos.x;
		const float startY = m_vecStartPos.y;

		const float endX = m_vecEndPos.x;
		const float endY = m_vecEndPos.y;

		const float dial = (endY - startY) / (endX - startX);

		*y = ((dial) * (x - startX)) + startY;
		return true;
	}
	void CLineComponent::Render(HDC hdc)
	{
		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		transparentBrush = (HBRUSH)SelectObject(hdc, oldBrush);

		Utils::DrawLine(hdc, m_vecStartPos, m_vecEndPos);
		pen = (HPEN)SelectObject(hdc, oldPen);

		DeleteObject(pen);
	}
}