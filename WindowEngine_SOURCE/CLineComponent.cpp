#include "CLineComponent.h"
#include "CBoxColliderComponent.h"
#include "CCameraComponent.h"
#include "CRenderer.h"

#include "CRenderManager.h"
#include "CTimeManager.h"

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
		if (m_pTriggerEvent != nullptr)
		{
			delete m_pTriggerEvent;
			m_pTriggerEvent = nullptr;
		}
	}

	void CLineComponent::Initialize()
	{
		CActor* owner = GetOwner();

		const CBoxColliderComponent* pCollider = owner->GetComponent<CBoxColliderComponent>();

		const Maths::Vector2& position = owner->GetPosition(); 
		const Maths::Vector2& size = pCollider->GetSize();
		const std::vector<Maths::Vector2>& axis = pCollider->GetAxis();

		const Maths::Vector2 halfSize = size * 0.5f;

		const Maths::Vector2 axeX = axis[0] * halfSize.x;
		const Maths::Vector2 axeY = axis[1] * halfSize.y;


		// 중심에서 위로 halfSize만큼 이동한 top을 기준으로,
		// m_fPercent만큼 위로 이동
		// 즉: bottom + (axeY * m_fPercent * -2)
		// 음수를 더해야 위로 이동 ((halfAxeY * -2 )* percent)
		const Maths::Vector2 baseLineCenter = position + ((axeY * -2.0f) * m_fPercent);

		// 좌우 끝점
		m_vecStartPos	= baseLineCenter - axeX;
		m_vecEndPos		= baseLineCenter + axeX;
	}

	bool CLineComponent::TickComponent()
	{
		return false;
	}

	bool CLineComponent::LastTickComponent()
	{
		if (m_pTriggerEvent != nullptr)
		{
			m_pTriggerEvent->first -= GET_SINGLE(TIME).DeltaTime();
			if (m_pTriggerEvent->first <= 0)
			{
				m_bTrigger = m_pTriggerEvent->second;
				delete m_pTriggerEvent;
				m_pTriggerEvent = nullptr;
			}
		}
		return false;
	}

	bool CLineComponent::CheckCollisionX(float x) const //범위 내에 있는지 확인
	{
		if (x >= m_vecStartPos.x && x <= m_vecEndPos.x)
		{
			return true;
		}
		return false;
	}

	bool CLineComponent::GetPositionY(float x, float* y) const //해당 범위의 Y값을 반환
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
		Maths::Vector2 startPos = m_vecStartPos;
		Maths::Vector2 endPos = m_vecEndPos;

		const CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();

		if (pCam != nullptr)
		{
			startPos = pCam->CaluatePosition(startPos);
			endPos = pCam->CaluatePosition(endPos);
		}
		GET_SINGLE(RENDER).Line(startPos, endPos);
	}

	void CLineComponent::EventTrigger(float waitTime, bool state)
	{
		if (m_pTriggerEvent != nullptr)
		{
			if (m_pTriggerEvent->first < waitTime)
			{		return;		}
		}
		m_pTriggerEvent = new  std::pair<FLOAT, BOOL>(waitTime, state);
	}

	void CLineComponent::FixedComponent()
	{
	}
}