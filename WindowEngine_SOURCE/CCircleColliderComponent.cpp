#include "CommonInclude.h"
#include "CCircleColliderComponent.h"
#include "CTransformComponent.h"

#include "CActor.h"
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
	void CCircleColliderComponent::BeginPlay()
	{
		//CColliderComponent::Initialize();
	}
	void CCircleColliderComponent::Release()
	{
	}

	bool CCircleColliderComponent::TickComponent()
	{
		return true;
	}
	bool CCircleColliderComponent::LastTickComponent()
	{
		return true;
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

		const INT posX = (INT)(pos.x + offset.x);
		const INT posY = (INT)(pos.y + offset.y);

		const float sizeX = m_vecSize.x * 0.5f;
		const float sizeY = m_vecSize.y * 0.5f;


		HBRUSH transPanrentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transPanrentBrush);

		HPEN pen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		Ellipse(hdc,
			(INT)(posX - sizeX), 
			(INT)(posY - sizeY),
			(INT)(posX + sizeX), 
			(INT)(posY + sizeY));

		SelectObject(hdc, oldBrush);
		pen = (HPEN)SelectObject(hdc, oldPen);
		DeleteObject(pen);
	}


	const bool CCircleColliderComponent::CheckCollision(CColliderComponent* other)
	{
		if (SUPER::CheckCollision(other) == false)
		{		return false;			}

		CColliderComponent::eColliderType colliderType = other->GetColliderType();
		switch (colliderType)
		{
		case Framework::CColliderComponent::eColliderType::Box:
			//return CColliderComponent::CheckCollisionBoxToCircle(other, this);

		case Framework::CColliderComponent::eColliderType::Circle:
			//return CColliderComponent::CheckCollisionCircleToCircle(this, other);

		case Framework::CColliderComponent::eColliderType::None:
			assert(false);
			break;
		default:
			break;
		}
		return false;
	}
	void CCircleColliderComponent::Initialize()
	{
	}
}
