#include "CommonInclude.h"
#include "CBoxColliderComponent.h"
#include "CTransformComponent.h"
#include "CRenderer.h"
#include "CActor.h"
#include "CRenderManager.h"
namespace Framework
{
	RECT CBoxColliderComponent::GetRect() const
	{
		const Maths::Vector2& pos = GetOwner()->GetPosition();
		const Maths::Vector2& size = GetSize();
		const float halfX = size.x * 0.5f;
		RECT rect =
		{
			static_cast<LONG>(pos.x - halfX),
			static_cast<LONG>(pos.y - size.y),
			static_cast<LONG>(pos.x + halfX),
			static_cast<LONG>(pos.y),
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

		if (pCam != nullptr)
		{
			pos = pCam->CaluatePosition(pos);
		}
		const Maths::Vector2 offsetPos = pos + m_vecOffset;

		if (((INT)m_fAngle % 180) == 0)
		{
			Maths::Vector2 start = { offsetPos.x - (m_vecSize.x * 0.5f), offsetPos.y - m_vecSize.y };
			Maths::Vector2 end = { offsetPos.x + (m_vecSize.x * 0.5f), offsetPos.y };
			GET_SINGLE(RENDER).FrameRect(start, end);
			//Utils::DrawRect(hdc, offsetPos, m_vecSize);
		}
		else
		{
			//Utils::DrawLine(hdc, offsetPos + m_vecPoints[0], offsetPos + m_vecPoints[1]);
			//Utils::DrawLine(hdc, offsetPos + m_vecPoints[1], offsetPos + m_vecPoints[3]);
			//Utils::DrawLine(hdc, offsetPos + m_vecPoints[2], offsetPos + m_vecPoints[3]);
			//Utils::DrawLine(hdc, offsetPos + m_vecPoints[2], offsetPos + m_vecPoints[0]);
			Maths::Vector2 start, end;

			start	= offsetPos + m_vecPoints[0];
			end		= offsetPos + m_vecPoints[1];
			GET_SINGLE(RENDER).Line(start, end);

			start = offsetPos + m_vecPoints[1];
			end = offsetPos + m_vecPoints[3];
			GET_SINGLE(RENDER).Line(start, end);

			start = offsetPos + m_vecPoints[2];
			end = offsetPos + m_vecPoints[3];
			GET_SINGLE(RENDER).Line(start, end);

			start = offsetPos + m_vecPoints[2];
			end = offsetPos + m_vecPoints[0];
			GET_SINGLE(RENDER).Line(start,end, Color(100,100,100), 1);

			//GET_SINGLE(RENDER).Line(offsetPos + m_vecPoints[1], offsetPos + m_vecPoints[3]);
			//GET_SINGLE(RENDER).Line(offsetPos + m_vecPoints[2], offsetPos + m_vecPoints[3]);
			//GET_SINGLE(RENDER).Line(offsetPos + m_vecPoints[2], offsetPos + m_vecPoints[0]);

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
			assert(false);
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

		// 회전 축(오브젝트의 로컬 X, Y 축)
		m_vecAxis.clear();
		m_vecAxis.push_back(Maths::Vector2(cos, sin));       // X축
		m_vecAxis.push_back(Maths::Vector2(-sin, cos));      // Y축

		const Maths::Vector2 halfSize = m_vecSize * 0.5f;

		// 원래 중심 기준일 때의 회전된 X/Y 벡터
		const Maths::Vector2 axeX = m_vecAxis[0] * halfSize.x;
		const Maths::Vector2 axeY = m_vecAxis[1] * halfSize.y;

		// 아래 중심을 기준으로 오프셋 보정
		// 중심에서 절반 높이만큼 위로 올린 위치가 기준이 됨
		const Maths::Vector2 pivotOffset = -axeY;

		// 최종 꼭짓점 계산 (pivot 기준 위치에서 오프셋 포함)
		const Maths::Vector2 pointOne = pivotOffset + (-axeX - axeY);  // 좌하
		const Maths::Vector2 pointTwo = pivotOffset + (axeX - axeY);  // 우하
		const Maths::Vector2 pointThree = pivotOffset + (-axeX + axeY);  // 좌상
		const Maths::Vector2 pointFour = pivotOffset + (axeX + axeY);  // 우상

		m_vecPoints.clear();
		m_vecPoints.push_back(pointOne);
		m_vecPoints.push_back(pointTwo);
		m_vecPoints.push_back(pointThree);
		m_vecPoints.push_back(pointFour);

	}

}
