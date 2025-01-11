#include "CAnimatorComponent.h"
#include "CAnimation.h"

namespace Framework
{
	CAnimatorComponent::CAnimatorComponent() :
		CComponent(Enums::eComponentType::Animator),
		m_pCurrentAnimation(nullptr),
		m_bLoop(false),
		m_mapAnimations{}
	{
	}

	CAnimatorComponent::~CAnimatorComponent()
	{
	}

	void CAnimatorComponent::Initialize()
	{
	}

	void CAnimatorComponent::Tick()
	{
		if (m_pCurrentAnimation)
		{
			m_pCurrentAnimation->Tick();
			if (m_pCurrentAnimation->IsCompleted() && m_bLoop)
			{
				m_pCurrentAnimation->Reset();
			}
		}
	}

	void CAnimatorComponent::LastTick()
	{
	}

	void CAnimatorComponent::Render(HDC hdc)
	{
	}

	void CAnimatorComponent::CreateAnimation(const std::wstring& name, Resource::CTexture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
	}

	CAnimation* CAnimatorComponent::FindAnimation(const std::wstring& name)
	{
		return nullptr;
	}

	void CAnimatorComponent::PlayAnimation(const std::wstring& name, bool loop)
	{
	}

}
