#pragma once
#include "CComponent.h"
#include "CAnimation.h"
using namespace Framework::Maths;
using namespace Framework::Resource;

namespace Framework
{
	class CActor;
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

		void CreateAnimation(const std::wstring& name, const CTexture* spriteSheet,
			const Vector2& leftTop/*, const Vector2& size, const Vector2& offset*/,
			UINT spriteLength, float duration);

		void CreateAnimationByFolder(const std::wstring& name, const std::wstring& path, const float duration);

		CAnimation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		inline bool IsCompletedAnimation() { return m_pCurrentAnimation->IsCompleted(); }

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

		CAnimatorComponent::Events* FindEvents(const std::wstring& name);

		static constexpr Enums::eComponentType StaticComponentType() { return Enums::eComponentType::Animator; }
		const Enums::eComponentType GetComponentType() const override { return StaticComponentType(); }

		friend CActor;
	private:
		CAnimatorComponent();
		virtual ~CAnimatorComponent();

		void BeginPlay()	override;
		bool TickComponent()			override;
		bool LastTickComponent()		override;

		void Render(HDC hdc)override;

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
