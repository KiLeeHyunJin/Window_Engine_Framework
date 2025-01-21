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
	void CCustomComponent::Initialize()
	{
	}
	void CCustomComponent::Release()
	{
	}
	void CCustomComponent::Tick()
	{
	}
	void CCustomComponent::LastTick()
	{
	}
	void CCustomComponent::Render(HDC hdc)
	{
	}
}