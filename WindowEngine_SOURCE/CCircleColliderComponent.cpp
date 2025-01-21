#include "CommonInclude.h"
#include "CCircleColliderComponent.h"
#include "CTransformComponent.h"

#include "CGameObject.h"
#include "CRenderer.h"

namespace Framework
{
	CCircleColliderComponent::CCircleColliderComponent():
		CColliderComponent(eColliderType::Circle), m_fRadius(0)
	{
	}
	CCircleColliderComponent::~CCircleColliderComponent()
	{
	}
	void CCircleColliderComponent::Initialize()
	{
	}
	void CCircleColliderComponent::Release()
	{
	}
	void CCircleColliderComponent::Tick()
	{
	}
	void CCircleColliderComponent::LastTick()
	{
	}
	void CCircleColliderComponent::Render(HDC hdc)
	{
		CTransformComponent* pTr = GetOwner()->GetComponent<CTransformComponent>();
		Maths::Vector2 pos = pTr->GetPos();

		if (Renderer::mainCamera)
		{
			pos = Renderer::mainCamera->CaluatePosition(pos);
		}

		Maths::Vector2 offset = GetOffset();
		HBRUSH transPanrentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transPanrentBrush);

		HPEN pen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Ellipse(hdc, 
			pos.x + offset.x, pos.y + offset.y,
			pos.x + offset.x + GetSize().x + 100,
			pos.y + offset.y + GetSize().y + 100);

		SelectObject(hdc, oldBrush);
		pen = (HPEN)SelectObject(hdc, oldPen);
		DeleteObject(pen);



	}
}
