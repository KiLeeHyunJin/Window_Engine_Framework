#include "CCameraComponent.h"
#include "CActor.h"

//extern Framework::CApplication application;

namespace Framework
{

	//void CCameraComponent::SetCameraRange(const Maths::Vector2& max)




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
	 
	Maths::Vector2 CCameraComponent::ScreenToWorldPoint(Maths::Vector2 vecScreen)
	{
		CActor* pTarget =
			m_pTarget != nullptr ?
			m_pTarget : GetOwner();

		const Maths::Vector2& lookPosition = pTarget->GetPosition();
		const Maths::Vector2Int& resolution = GET_SINGLE(RENDER).GetResolution();
		return vecScreen + (lookPosition - (Maths::Vector2(resolution.x * 0.5f, resolution.y * 0.5f)));
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
		const Maths::Vector2 resolutionHalf = resolutionScreen * 0.5f;



		Maths::Vector2 diffPos;
		if (m_vecFollowMin.HasValue() && m_vecFollowMax.HasValue())
		{
			const Maths::Vector2 diff = (lookPosition - resolutionHalf) - m_vecDistance;//Ÿ�ٰ� ī�޶��� �Ÿ�

			diffPos.x = Maths::Clamp(diff.x, m_vecFollowMin.x, m_vecFollowMax.x);
			diffPos.y = Maths::Clamp(diff.y, m_vecFollowMin.y, m_vecFollowMax.y);
		}

		Maths::Vector2 adjustPos;
		if (m_vecMax.HasValue())
		{
			adjustPos.x = Maths::Clamp(lookPosition.x, resolutionHalf.x + diffPos.x, m_vecMax.x - diffPos.x);
			adjustPos.y = Maths::Clamp(lookPosition.y, resolutionHalf.y + diffPos.y, m_vecMax.y - diffPos.y);
		}

		//����� ī�޶� �߾ӿ� ��ġ�ϰ� �Ϸ��� = ( ����� ��ġ - �ػ� * 0.5 )
		m_vecDistance = (adjustPos - resolutionHalf) - diffPos;
	}


	void CCameraComponent::Render(HDC hdc)
	{
	}

}