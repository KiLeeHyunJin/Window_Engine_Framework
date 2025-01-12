#pragma once
#include "CAnimatorComponent.h"

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
		if (m_pCurrentAnimation)
		{
			m_pCurrentAnimation->Render(hdc);
		}
	}

	void CAnimatorComponent::CreateAnimation(const std::wstring& name, CTexture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		CAnimation* pAnim = nullptr;
		pAnim = FindAnimation(name);
		if (pAnim != nullptr)
		{
			return;
		}
		pAnim = new CAnimation();
		pAnim->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);
		pAnim->SetOwner(this);
		m_mapAnimations.insert(std::make_pair(name,pAnim));
	}

	CAnimation* CAnimatorComponent::FindAnimation(const std::wstring& name)
	{
		auto iter = m_mapAnimations.find(name);
		if (iter == m_mapAnimations.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	void CAnimatorComponent::PlayAnimation(const std::wstring& name, bool loop)
	{
		CAnimation* pAnim = FindAnimation(name);
		if (pAnim != nullptr)
		{
			if (m_bLoop != loop)
			{
				m_bLoop = loop;
			}
			m_pCurrentAnimation = pAnim;
			m_pCurrentAnimation->Reset();
		}
	}

}
