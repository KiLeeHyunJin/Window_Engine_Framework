#pragma once
#include "CComponent.h"
#include "CAnimation.h"
using namespace Framework::Maths;
using namespace Framework::Resource;

namespace Framework
{

	class CAnimatorComponent :
public CComponent
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{	mEvent = std::move(func);	}
			void operator()()
			{	if (mEvent)	{	mEvent;	}	}
			std::function<void()> mEvent;
		};
		struct Events
		{
			Event m_StartEvent;
			Event m_CompleteEvent;
			Event m_EndEvent;
		};

		CAnimatorComponent();
		virtual ~CAnimatorComponent();

		void Initialize() override;
		void Tick() override;
		void LastTick()override;

		void Render(HDC hdc)override;

		void CreateAnimation(const std::wstring& name, CTexture* spriteSheet,
			Vector2 leftTop, Vector2 size, Vector2 offset,
			UINT spriteLength, float duration);
		void CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, Vector2 offset, float duration);

		CAnimation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		bool IsCompletedAnimation() { return m_pCurrentAnimation->IsCompleted(); }

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

		CAnimatorComponent::Events* FindEvents(const std::wstring& name);
	private:
		void EndAnimation();
		void StartAnimation(CAnimation* const  pAnim);
		// CComponent을(를) 통해 상속됨
		void Release() override;

		CAnimation* m_pCurrentAnimation;
		std::map<std::wstring, CAnimation*> m_mapAnimations;
		std::map<std::wstring, Events*> m_mapEvents;
		
		bool m_bLoop;
	};


}
