#pragma once
#include "CEntity.h"
#include "CommonInclude.h"

namespace Framework
{
	class CUIManager;

	class CUIBase : public CEntity
	{
	public:
		CUIBase();
		virtual ~CUIBase();

		void SetFullScreen(bool state)					{ m_bFullScreen = state; }
		void SetParent(CUIBase* pParent)				{ m_pParent = pParent; }

		void AddChildUI(CUIBase* pChildUI);
		void RemoveChildUI(CUIBase* pChildUI);

		Enums::eUILayer GetLayer() const				{ return m_eLayerType; }
		__inline Enums::eUIType GetType() const			{ return m_eType; }
		__inline bool			GetFullScreen() const	{ return m_bFullScreen; }

		Maths::Vector2			GetWorldPosition() const{ return m_vecRenderPos; }
		__inline Maths::Vector2 GetLocalPosition() const{ return m_vecPos; }
		__inline Maths::Vector2 GetScale()	const		{ return m_vecSize; }
		__inline bool			GetChangeHierarchy() const { return m_bChangeHierarchy; }

		__inline void SetLocalPosition(Maths::Vector2 pos)	{ m_vecPos = pos; }
		__inline void SetScale(Maths::Vector2 size)		{ m_vecSize = size; }

	protected:
		__inline void SetChangeHierarchy(bool state)	{ m_bChangeHierarchy = state; }
		__inline void SetType(Enums::eUIType type)		{ m_eType = type; }
		__inline void SetDrag(bool state)				{ m_bDraggable = state; }
		__inline void SetWorldObject(bool state)		{ m_bWorldObject = state; }
		__inline bool GetDragable() const				{ return m_bDraggable; }
		Maths::Vector2 m_vecRenderPos;

		friend CUIManager;
	private:

#pragma region  Basic Event
		void Initialize();
		void Release();

		void Tick();
		void LastTick();

		void Render(HDC hdc) const;
#pragma endregion

		void Active();
		void InActive();

		void Clear();

#pragma region  UI Event
		void Over();

		void Enter();
		void Exit();

		void Down();
		void Up();
#pragma endregion

#pragma region Virtual
		virtual void OnInitialize();
		virtual void OnRelease();

		virtual void OnActive();
		virtual void OnInActive();

		virtual void OnTick();
		virtual void OnLastTick();

		virtual void OnRender(HDC hdc) const;
		virtual void OnClear();

		virtual void OnEnter();
		virtual void OnExit();

		virtual void OnDown();
		virtual void OnUp();

		virtual void OnClick();
#pragma endregion

		__inline void	MouseOnCheck();
		__inline void	UpdatePosition();

		__inline void	SetUIIndex(INT idx)	{ m_iIndex = idx; }
		__inline INT	GetUIIndex() const		{ return m_iIndex; }

		bool m_bFullScreen;
		bool m_bEnable;

		bool m_bDraggable;
		bool m_bIsDrag;

		bool m_bWorldObject;
		bool m_bChangeHierarchy;
		
		bool m_bPrevMouseOn;
		bool m_bCurMouseOn;

		bool m_bPrevMouseDown;
		bool m_bCurMouseDown;

		bool m_bFocusOn;
		CUIBase* m_pParent;

		INT m_iIndex;
		Enums::eUIType m_eType;
		Enums::eUILayer m_eLayerType;
		Maths::Vector2 m_vecPos;
		Maths::Vector2 m_vecSize;
		Maths::Vector2 m_vecDragStartPos;

		std::vector<CUIBase*> m_vecChilds;
	};
}

