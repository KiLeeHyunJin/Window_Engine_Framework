#pragma once
#include "CEntity.h"
#include "CommonInclude.h"

namespace Framework
{
	class CUIManager;

	class CUIBase : public CEntity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent) { mEvent; }
			}
			std::function<void()> mEvent;
		};
		struct Events
		{
			Event m_StartEvent;
			Event m_CompleteEvent;
			Event m_EndEvent;
		};


		CUIBase();
		virtual ~CUIBase();
		
		void SetFullScreen(bool state) { m_bFullScreen = state; }

		Maths::Vector2 GetPosition() const	{ return m_vecPos; }
		Maths::Vector2 GetScale()	const	{ return m_vecSize; }

		void SetPosition(Maths::Vector2 pos){ m_vecPos = pos; }
		void SetScale(Maths::Vector2 size)	{ m_vecSize = size; }

		friend CUIManager;
	private:
		void Initialize();
		void Tick();
		void LastTick();
		void Release();
		void Render(HDC hdc);

		void Active();
		void InActive();

		Enums::eUIType GetType() const { return m_eType; }
		bool GetFullScreen() const { return m_bFullScreen; }

		virtual void OnInitialize();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnTick();
		virtual void OnLastTick();
		virtual void OnClear();



		Enums::eUIType m_eType;

		bool m_bFullScreen;
		bool m_bEnable;

		Maths::Vector2 m_vecPos;
		Maths::Vector2 m_vecSize;
	};
}

