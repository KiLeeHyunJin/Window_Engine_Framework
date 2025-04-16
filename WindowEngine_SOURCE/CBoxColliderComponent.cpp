#include "CommonInclude.h"
#include "CBoxColliderComponent.h"
#include "CTransformComponent.h"
#include "CRenderer.h"
#include "CActor.h"

namespace Framework
{
	RECT CBoxColliderComponent::GetRect()
	{
		const Maths::Vector2& pos = GetOwner()->GetPosition();
		const Maths::Vector2& size = GetSize();
		RECT rect =
		{
			static_cast<LONG>((pos.x - (size.x * 0.5f))),
			static_cast<LONG>((pos.y - (size.y * 0.5f))),
			static_cast<LONG>((pos.x + (size.x * 0.5f))),
			static_cast<LONG>((pos.y + (size.y * 0.5f))),
		};
		return rect;
	}

	CBoxColliderComponent::CBoxColliderComponent() :
		CColliderComponent(eColliderType::Box)
	{
		 //m_vecSize = (Maths::Vector2(50,50));
	}

	CBoxColliderComponent::~CBoxColliderComponent()
	{
	}

	void CBoxColliderComponent::BeginPlay()
	{
		//CColliderComponent::Initialize();
	}

	void CBoxColliderComponent::Release()
	{
	}

	bool CBoxColliderComponent::TickComponent()
	{
		return true;
	}

	bool CBoxColliderComponent::LastTickComponent()
	{
		return true;
	}

	void CBoxColliderComponent::Render(HDC hdc)
	{
		//const CTransformComponent* pTr = GetOwner()->GetTransformComponent();
		Maths::Vector2 pos = GetOwner()->GetPosition();
		const CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
		if (pCam != nullptr)
		{
			pos = pCam->CaluatePosition(pos);
		}
		const Maths::Vector2 offsetPos = pos + m_vecOffset;
		Utils::DrawRect(hdc, offsetPos, m_vecSize);

		//HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc,transparentBrush);
		//
		//HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		//HPEN oldPen = (HPEN)SelectObject(hdc, pen);


		//transparentBrush = (HBRUSH)SelectObject(hdc, oldBrush);
		//pen = (HPEN)SelectObject(hdc, oldPen);

		//DeleteObject(pen);
	}

	const bool CBoxColliderComponent::CheckCollision(CColliderComponent* other)
	{
		if (SUPER::CheckCollision(other) == false)
		{	return	false;		}

		CColliderComponent::eColliderType colliderType = other->GetColliderType();

		switch (colliderType)
		{
		case Framework::CColliderComponent::eColliderType::Box:
			return CColliderComponent::CheckCollisionBoxToBox(this, other);
			break;
		case Framework::CColliderComponent::eColliderType::Circle:
			return CColliderComponent::CheckCollisionBoxToCircle(this, other);

		case Framework::CColliderComponent::eColliderType::None:
			assert(true);
			break;
		default:
			break;
		}
		return false;
	}

}
