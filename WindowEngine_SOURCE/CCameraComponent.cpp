#include "CCameraComponent.h"
#include "CActor.h"
#include "CTransformComponent.h"
//#include "CApplication.h"
#include "CRenderManager.h"
//extern Framework::CApplication application;

namespace Framework
{
	CCameraComponent::CCameraComponent():
		CComponent(Enums::eComponentType::Camera),
		m_pTarget(nullptr)//, m_vecResolution(Maths::Vector2::Zero)
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
		CActor* pTarget = 
			m_pTarget != nullptr ? 
			m_pTarget : GetOwner();

		//CTransformComponent* pTr = pTarget->GetComponent<CTransformComponent>();
		m_vecLookPosition = pTarget->GetPosition();
		m_vecDistance = m_vecLookPosition - (m_vecDistance * 0.5f);
		return true;
	}
	 
	bool CCameraComponent::LastTickComponent()
	{
		return true;
	}

	void CCameraComponent::Render(HDC hdc)
	{
	}
}