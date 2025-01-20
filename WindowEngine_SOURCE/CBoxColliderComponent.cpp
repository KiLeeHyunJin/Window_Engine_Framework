#include "CommonInclude.h"
#include "CBoxColliderComponent.h"
#include "CTransformComponent.h"

#include "CGameObject.h"

namespace Framework
{

	CBoxColliderComponent::CBoxColliderComponent() :
		CColliderComponent()
	{
	}

	CBoxColliderComponent::~CBoxColliderComponent()
	{
	}

	void CBoxColliderComponent::Initialize()
	{
	}

	void CBoxColliderComponent::Release()
	{
	}

	void CBoxColliderComponent::Tick()
	{
	}

	void CBoxColliderComponent::LastTick()
	{
	}

	void CBoxColliderComponent::Render(HDC hdc)
	{
		CTransformComponent* pTr = GetOwner()->GetComponent<CTransformComponent>();
		Maths::Vector2 pos = pTr->GetPos() + m_vecOffset;
		Maths::Vector2 offsetPos = pos + m_vecOffset;

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc,transparentBrush);

		HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Rectangle(hdc, offsetPos.x , offsetPos.y, offsetPos.x, offsetPos.y);

		transparentBrush = (HBRUSH)SelectObject(hdc, oldBrush);
		pen = (HPEN)SelectObject(hdc, oldPen);

		DeleteObject(pen);
	}

}
