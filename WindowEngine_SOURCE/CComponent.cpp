#include "CComponent.h"

Framework::CComponent::CComponent(Enums::eComponentType eComopnentType) : 
m_eComponentType(eComopnentType),
m_pOwner(nullptr)
{
}

Framework::CComponent::~CComponent()
{
}

void Framework::CComponent::Initialize()
{
}

void Framework::CComponent::Tick()
{
}

void Framework::CComponent::LastTick()
{
}

void Framework::CComponent::Release()
{
}

void Framework::CComponent::Render(HDC hDC)
{
}
