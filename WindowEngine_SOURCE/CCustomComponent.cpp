#include "CCustomComponent.h"

namespace Framework
{
	CCustomComponent::CCustomComponent():
		CComponent(Enums::eComponentType::Custom)
	{
	}
	CCustomComponent::~CCustomComponent()
	{
	}
	void CCustomComponent::OnCollisionEnter(CColliderComponent* other)
	{

	}
	void CCustomComponent::OnCollisionStay(CColliderComponent* other)
	{
	}
	void CCustomComponent::OnCollisionExit(CColliderComponent* other)
	{
	}
	void CCustomComponent::BeginPlay()
	{
	}
	void CCustomComponent::Release()
	{
	}
	bool CCustomComponent::Tick()
	{
		return true;
	}
	bool CCustomComponent::LastTick()
	{
		return true;
	}
	void CCustomComponent::Render(HDC hdc)
	{
	}
}