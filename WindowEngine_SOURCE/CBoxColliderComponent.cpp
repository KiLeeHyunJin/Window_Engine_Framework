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
		const Maths::Vector2 offsetPos = pos + m_vecOffset;

		if (pCam != nullptr)
		{
			pos = pCam->CaluatePosition(pos);
		}


		if (m_fAngle == 0)
		{
			Utils::DrawRect(hdc, offsetPos, m_vecSize);
		}
		else
		{
			FLOAT radian = m_fAngle * (Maths::PI / 180);
			FLOAT cos_r = std::cos(radian), sin_r = std::sin(radian);
			Maths::Vector2 axeX(cos_r, sin_r);    // x√‡
			Maths::Vector2 axeY(-sin_r, cos_r);   // y√‡

			std::vector<Maths::Vector2> adjustPoint;
			adjustPoint.reserve(4);

			for (int dx : {-1, 1}) {
				for (int dy : {-1, 1}) 
				{
					adjustPoint.push_back(
						offsetPos +
						Maths::Vector2(
							axeX * (dx * m_vecSize.x * 0.5f) +
							axeY * (dy * m_vecSize.y * 0.5f)));
				}
			}
			Utils::DrawLine(hdc, adjustPoint[0], adjustPoint[1]);
			Utils::DrawLine(hdc, adjustPoint[1], adjustPoint[3]);
			Utils::DrawLine(hdc, adjustPoint[2], adjustPoint[3]);
			Utils::DrawLine(hdc, adjustPoint[2], adjustPoint[0]);
		}

	


	
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
