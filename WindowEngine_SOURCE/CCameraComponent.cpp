#include "CCameraComponent.h"
#include "CActor.h"
#include "CTransformComponent.h"
//#include "CApplication.h"
#include "CRenderManager.h"
#include "Define.h"
//extern Framework::CApplication application;

namespace Framework
{
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

		if (m_vecMin.HasValue() && m_vecMax.HasValue())
		{
			Maths::Vector2 clampPosition;
			clampPosition.x = Maths::Clamp(lookPosition.x, m_vecMin.x, m_vecMax.x);
			clampPosition.y = Maths::Clamp(lookPosition.y, m_vecMin.y, m_vecMax.y);

			m_vecDistance = clampPosition - (resolution * 0.5f);
		}
		else
		{
			m_vecDistance = lookPosition - (resolution * 0.5f);
		}
		
		return true;
	}

	void CCameraComponent::Render(HDC hdc)
	{
	}
}