#include "CColliderComponent.h"
#include "CGameObject.h"
#include "CCustomComponent.h"

namespace Framework
{
	UINT32 CColliderComponent::m_collId = 1;

	CColliderComponent::CColliderComponent():
		CComponent(Enums::eComponentType::Collider)
	{	}

	CColliderComponent::CColliderComponent(eColliderType colliderType):
		CComponent(Enums::eComponentType::Collider), m_iColliderId(m_collId++),
		m_vecSize(Maths::Vector2::One), m_eColliderType(colliderType)
	{
	}
	CColliderComponent::~CColliderComponent()
	{
	}
	void CColliderComponent::Initialize()
	{
	}
	void CColliderComponent::Release()
	{
	}
	void CColliderComponent::Tick()
	{
	}
	void CColliderComponent::LastTick()
	{
	}
	void CColliderComponent::Render(HDC hdc)
	{
	}

	void CColliderComponent::OnCollisionEnter(CColliderComponent* other)
	{
		CCustomComponent* pCustom = GetOwner()->GetComponent<CCustomComponent>();
		pCustom->OnCollisionEnter(other);
	}

	void CColliderComponent::OnCollisionStay(CColliderComponent* other)
	{
		CCustomComponent* pCustom = GetOwner()->GetComponent<CCustomComponent>();
		pCustom->OnCollisionStay(other);
	}

	void CColliderComponent::OnCollisionExit(CColliderComponent* other)
	{
		CCustomComponent* pCustom = GetOwner()->GetComponent<CCustomComponent>();
		pCustom->OnCollisionExit(other);
	}
}