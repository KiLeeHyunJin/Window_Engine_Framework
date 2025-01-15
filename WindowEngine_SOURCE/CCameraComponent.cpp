#include "CCameraComponent.h"
#include "CGameObject.h"
#include "CTransformComponent.h"
#include "CApplication.h"

extern Framework::CApplication application;

namespace Framework
{
	CCameraComponent::CCameraComponent():
		CComponent(Enums::eComponentType::Camera),
		m_pTarget(nullptr)
	{
		m_vecResolution = application.GetResolution();
	}
	CCameraComponent::~CCameraComponent()
	{
	}

	void CCameraComponent::Initialize()
	{
	}
	void CCameraComponent::Release()
	{
	}
	void CCameraComponent::Tick()
	{
		CGameObject* pTarget = 
			m_pTarget != nullptr ? 
			m_pTarget : GetOwner();

		CTransformComponent* pTr = pTarget->GetComponent<CTransformComponent>();
		m_vecLookPosition = pTr->GetPos();
		m_vecDistance = m_vecLookPosition - (m_vecDistance * 0.5f);
	}
	 
	void CCameraComponent::LastTick()
	{

	}

	void CCameraComponent::Render(HDC hdc)
	{
	}
}