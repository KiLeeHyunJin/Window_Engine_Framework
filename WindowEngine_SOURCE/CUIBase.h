#pragma once
#include "CEntity.h"
#include "CommonInclude.h"

namespace Framework
{
	class CUIManager;

	class CUIBase : public CEntity
	{
	public:
		//struct Event
		//{
		//	void operator=(std::function<void()> func)
		//	{
		//		mEvent = std::move(func);
		//	}
		//	void operator()()
		//	{
		//		if (mEvent) { mEvent; }
		//	}
		//	std::function<void()> mEvent;
		//};
		//struct Events
		//{
		//	Event m_StartEvent;
		//	Event m_CompleteEvent;
		//	Event m_EndEvent;
		//};


		CUIBase();
		virtual ~CUIBase();

		void SetFullScreen(bool state) { m_bFullScreen = state; }
		void SetParent(CUIBase* pParent) { m_pParent = pParent; }

		__inline Enums::eUIType GetType() const { return m_eType; }
		__inline bool GetFullScreen() const { return m_bFullScreen; }

		__inline Maths::Vector2 GetPosition() const	{ return m_vecPos; }
		__inline Maths::Vector2 GetScale()	const	{ return m_vecSize; }

		__inline void SetPosition(Maths::Vector2 pos){ m_vecPos = pos; }
		__inline void SetScale(Maths::Vector2 size)	{ m_vecSize = size; }

	protected:
		void			SetDrag(bool state) { m_bDragable = state; }
		__inline bool	GetDragable() const { return m_bDragable; }

		Maths::Vector2 m_vecPos;
		Maths::Vector2 m_vecSize;
		bool m_bMouseOn;

		friend CUIManager;
	private:
		void Initialize();
		void Release();

		void Tick();
		void LastTick();
		
		void Render(HDC hdc);  

		void Active();
		void InActive();

		virtual void OnInitialize();
		virtual void OnRelease();

		virtual void OnActive();
		virtual void OnInActive();

		virtual void OnTick();
		virtual void OnLastTick();

		virtual void OnRender(HDC hdc);
		virtual void OnClear();

		__inline void	SetUIIndex(UINT idx) { m_iIndex = idx; }
		__inline UINT	GetUIIndex() const { return m_iIndex; }

		std::vector<CUIBase*> m_vecChilds;
		CUIBase* m_pParent;

		Enums::eUIType m_eType;
		UINT m_iIndex;

		bool m_bFullScreen;
		bool m_bEnable;
		bool m_bDragable;
	};
}

