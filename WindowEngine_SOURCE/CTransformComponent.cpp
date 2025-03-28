#include "CTransformComponent.h"

Framework::CTransformComponent::CTransformComponent():
	CComponent(Enums::eComponentType::Transform),
	m_fRot(0), m_vecScale(Maths::Vector2::One), m_vecPos(Maths::Vector2::Zero)
{
}

Framework::CTransformComponent::~CTransformComponent()
{
}

void Framework::CTransformComponent::Initialize()
{
}

void Framework::CTransformComponent::Release()
{
}

bool Framework::CTransformComponent::Tick()
{
	return true;
}

bool Framework::CTransformComponent::LastTick()
{
	return true;
}

void Framework::CTransformComponent::Render(HDC hdc)
{
}
