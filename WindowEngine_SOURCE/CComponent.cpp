#include "CComponent.h"

Framework::CComponent::CComponent(Enums::eComponentType eComopnentType) : 
m_eComponentType(eComopnentType),
m_pOwner(nullptr)
{
}

Framework::CComponent::~CComponent()
{
}

void Framework::CComponent::BeginPlay()
{
}

bool Framework::CComponent::TickComponent()
{
	return true;
}

bool Framework::CComponent::LastTickComponent()
{
	return true;
}

void Framework::CComponent::Release()
{
}

void Framework::CComponent::Render(HDC hDC)
{
}
