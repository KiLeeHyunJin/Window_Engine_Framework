#include "CColliderComponent.h"
#include "CActor.h"
#include "CCustomComponent.h"

namespace Framework
{
	UINT32 CColliderComponent::m_collId = 1;

	CColliderComponent::CColliderComponent():
		CComponent(Enums::eComponentType::Collider), m_eColliderType(eColliderType::None), m_iColliderId(m_collId++),
		m_vecSize(Maths::Vector2::One)
	{	
	}

	CColliderComponent::CColliderComponent(eColliderType colliderType):
		CComponent(Enums::eComponentType::Collider), m_iColliderId(m_collId++),
		m_vecSize(Maths::Vector2::One), m_eColliderType(colliderType)
	{
	}

	CColliderComponent::~CColliderComponent()
	{
	}
	void CColliderComponent::BeginPlay()
	{
	}
	void CColliderComponent::Release()
	{
	}
	bool CColliderComponent::Tick()
	{
		return true;
	}
	bool CColliderComponent::LastTick()
	{
		return true;
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