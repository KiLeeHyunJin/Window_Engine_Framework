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
		m_vecPoints.resize(4);
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
		Maths::Vector2 pos = GetOwner()->GetPosition();
		const CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
		const Maths::Vector2 offsetPos = pos + m_vecOffset;

		if (pCam != nullptr)
		{
			pos = pCam->CaluatePosition(pos);
		}

		if (((INT)m_fAngle % 180) == 0)
		{
			Utils::DrawRect(hdc, offsetPos, m_vecSize);
		}
		else
		{
			Utils::DrawLine(hdc, offsetPos + m_vecPoints[0], offsetPos + m_vecPoints[1]);
			Utils::DrawLine(hdc, offsetPos + m_vecPoints[1], offsetPos + m_vecPoints[3]);
			Utils::DrawLine(hdc, offsetPos + m_vecPoints[2], offsetPos + m_vecPoints[3]);
			Utils::DrawLine(hdc, offsetPos + m_vecPoints[2], offsetPos + m_vecPoints[0]);
		}
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
			//return CColliderComponent::CheckCollisionBoxToCircle(this, other);

		case Framework::CColliderComponent::eColliderType::None:
			assert(true);
			break;
		default:
			break;
		}
		return false;
	}

	void CBoxColliderComponent::Initialize()
	{
		const FLOAT radian = m_fAngle * (Maths::PI / 180);
		const FLOAT cos = std::cos(radian);
		const FLOAT sin = std::sin(radian);

		m_vecAxis.clear();
		m_vecAxis.push_back(Maths::Vector2(cos, sin));
		m_vecAxis.push_back(Maths::Vector2(-sin, cos));
		//축 방향 저장

		const Maths::Vector2 halfSize = m_vecSize * 0.5f;

		const Maths::Vector2 axeX(m_vecAxis[0] * halfSize.x);
		const Maths::Vector2 axeY(m_vecAxis[1] * halfSize.y);

		const Maths::Vector2 pointOne(
			Maths::Vector2(-axeX + -axeY));

		const Maths::Vector2 pointTwo(
			Maths::Vector2(axeX + -axeY));

		const Maths::Vector2 pointThree(
			Maths::Vector2(-axeX + axeY));

		const Maths::Vector2 pointFour(
			Maths::Vector2(axeX + axeY));

		m_vecPoints.clear();
		m_vecPoints.push_back(pointOne);
		m_vecPoints.push_back(pointTwo);
		m_vecPoints.push_back(pointThree);
		m_vecPoints.push_back(pointFour);

	}

}
