#include "CCameraComponent.h"
#include "CActor.h"

//extern Framework::CApplication application;

namespace Framework
{

	void CCameraComponent::SetCameraRange(const Maths::Vector2& min, const Maths::Vector2& max)
	{
		const Maths::Vector2Int& resolution = GET_SINGLE(RENDER).GetResolution();
		const Maths::Vector2 halfResolution(static_cast<FLOAT>(resolution.x >> 1), static_cast<FLOAT>(resolution.y >> 1));
		m_vecMin = min + halfResolution;
		m_vecMax = max - halfResolution;
	}

	void CCameraComponent::SetTarget(CActor* pTarget)
	{
		m_pTarget = pTarget;		
		AdjustDistance(m_pTarget->GetPosition(), GET_SINGLE(RENDER).GetResolution());
	}

	CCameraComponent::CCameraComponent():
		CComponent(Enums::eComponentType::Camera)
	{
	}
	CCameraComponent::~CCameraComponent()
	{
	}

	void CCameraComponent::BeginPlay()
	{
		//SetResolution(GET_SINGLE(RENDER).GetResolution());
	}
	void CCameraComponent::Release()
	{
	}

	bool CCameraComponent::TickComponent()
	{
		return true;
	}
	 
	bool CCameraComponent::LastTickComponent()
	{
		CActor* pTarget =
			m_pTarget != nullptr ?
			m_pTarget : GetOwner();

		const Maths::Vector2& lookPosition = pTarget->GetPosition();
		const Maths::Vector2& resolution = GET_SINGLE(RENDER).GetResolution();
		
		AdjustDistance(lookPosition, resolution);

		return true;
	}

	void CCameraComponent::AdjustDistance(const Maths::Vector2& lookPosition, const Maths::Vector2& resolutionScreen)
	{
		const Maths::Vector2 diff = (lookPosition - m_vecDistance) - (resolutionScreen * 0.5f);

		if (m_vecFollowMin.HasValue() && m_vecFollowMax.HasValue())
		{
			if (diff.x >= m_vecFollowMin.x && diff.x <= m_vecFollowMax.x)
			{
				if (diff.y <= m_vecFollowMin.y && diff.y >= m_vecFollowMax.y)
				{
					return;
				}
			}
		}

		Maths::Vector2 adjustPos = lookPosition;
		if (Maths::Clamp(&adjustPos.x, m_vecMin.x, m_vecMax.x) == false) //카메라 촬영 범위를 벗어나지 않음
		{

		}
		if (Maths::Clamp(&adjustPos.y, m_vecMin.y, m_vecMax.y) == false)
		{

		}


		if (ClampRange(lookPosition,m_vecMin, m_vecMax, adjustPos))
		{
			m_vecDistance = adjustPos - (resolutionScreen * 0.5f);
			return;
		}
		else
		{
			if (ClampRange(lookPosition, m_vecFollowMin, m_vecFollowMax, adjustPos))
			{

			}
		}
		m_vecDistance = adjustPos - (resolutionScreen * 0.5f) - diff;

	}

	bool CCameraComponent::ClampRange(const Maths::Vector2& target,const Maths::Vector2& min, const Maths::Vector2& max , Maths::Vector2& adjustValue)
	{
		if (m_vecMin.HasValue() && m_vecMax.HasValue())
		{
			adjustValue.x = Maths::Clamp<FLOAT>(target.x, min.x, max.x);
			adjustValue.y = Maths::Clamp<FLOAT>(target.y, max.y, min.y);

			const bool state = adjustValue.x == min.x || adjustValue.x == max.x;
			const bool state2 = adjustValue.y == min.y || adjustValue.y == max.y;

			return state || state2;
		}
		adjustValue = target;
		return false;
	}


	void CCameraComponent::Render(HDC hdc)
	{
	}

}