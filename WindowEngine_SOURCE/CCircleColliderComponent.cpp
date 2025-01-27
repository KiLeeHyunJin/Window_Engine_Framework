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

		CCameraComponent* mainCam = Renderer::CRenderer::GetMainCamera();
		if (mainCam != nullptr)
		{
			pos = mainCam->CaluatePosition(pos);
		}

		const Maths::Vector2 offset = GetOffset();

		const UINT posX = pos.GetX() + offset.GetX();
		const UINT posY = pos.GetY() + offset.GetY();

		const float sizeX = m_vecSize.GetX() * 0.5f;
		const float sizeY = m_vecSize.GetY() * 0.5f;


		HBRUSH transPanrentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transPanrentBrush);

		HPEN pen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Ellipse(hdc,
			posX - sizeX, posY - sizeY,
			posX + sizeX, posY + sizeY
		);

		SelectObject(hdc, oldBrush);
		pen = (HPEN)SelectObject(hdc, oldPen);
		DeleteObject(pen);



	}
}
