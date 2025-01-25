#include "CCameraComponent.h"
#include "CGameObject.h"
#include "CTransformComponent.h"
#include "CApplication.h"

extern Framework::CApplication application;

namespace Framework
{
	CCameraComponent::CCameraComponent():
		CComponent(Enums::eComponentType::Camera),
		m_pTarget(nullptr), m_vecResolution(Maths::Vector2::Zero)
	{
	}
	CCameraComponent::~CCameraComponent()
	{
	}

	void CCameraComponent::Initialize()
	{
		SetResolution(application.GetResolution());
	}
	void CCameraComponent::Release()
	{
	}
	void CCameraComponent::Tick()
	{
		CGameObject* pTarget = 
			m_pTarget != nullptr ? 
			m_pTarget : GetOwner();

		CTransformComponent* pTr = pTarget->GetTransformComponent();
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