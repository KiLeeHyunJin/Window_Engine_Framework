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
			Events* events = FindEvents(m_pCurrentAnimation->GetName());
			if (m_pCurrentAnimation->IsCompleted())
			{
				if (events)
				{
					events->m_CompleteEvent();
				}
				if (m_bLoop)
				{
					m_pCurrentAnimation->Reset();
				}
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
			EndAnimation();
			StartAnimation(pAnim);
		}
	}

	std::function<void()>& CAnimatorComponent::GetStartEvent(const std::wstring& name)
	{
		Events* pEvents = FindEvents(name);
		return pEvents->m_StartEvent.mEvent;
		// TODO: 여기에 return 문을 삽입합니다.
	}

	std::function<void()>& CAnimatorComponent::GetCompleteEvent(const std::wstring& name)
	{
		Events* pEvents = FindEvents(name);
		return pEvents->m_CompleteEvent.mEvent;

		// TODO: 여기에 return 문을 삽입합니다.
	}

	std::function<void()>& CAnimatorComponent::GetEndEvent(const std::wstring& name)
	{
		Events* pEvents = FindEvents(name);
		return pEvents->m_EndEvent.mEvent;
		// TODO: 여기에 return 문을 삽입합니다.
	}

	CAnimatorComponent::Events* CAnimatorComponent::FindEvents(const std::wstring& name)
	{
		const auto& iter = m_mapEvents.find(name);
		if (iter == m_mapEvents.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	void CAnimatorComponent::EndAnimation()
	{
		if (m_pCurrentAnimation != nullptr)
		{
			Events* oldEvents = FindEvents(m_pCurrentAnimation->GetName());
			if (oldEvents)
			{
				oldEvents->m_EndEvent();
			}
		}
	}

	void CAnimatorComponent::StartAnimation(CAnimation* const pAnim)
	{
		m_pCurrentAnimation = pAnim;
		m_pCurrentAnimation->Reset();
		Events* newEvents = FindEvents(m_pCurrentAnimation->GetName());
		if (newEvents)
		{
			newEvents->m_StartEvent();
		}
	}

	void CAnimatorComponent::Release()
	{
		for (const auto& pair : m_mapAnimations)
		{
			delete pair.second;
		}
		for (const auto& pair : m_mapEvents)
		{
			delete pair.second;
		}
		m_mapAnimations.clear();
		m_mapEvents.clear();
	}

}
