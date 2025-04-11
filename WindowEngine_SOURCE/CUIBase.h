#pragma once
#include "CEntity.h"
#include "CommonInclude.h"

namespace Framework
{
	namespace Manager
	{
		class CUIManager;
	}

	class CUIBase : public CEntity
	{
	public:
		CUIBase();
		virtual ~CUIBase();

		void AddChildUI		(CUIBase* pChildUI);
		void RemoveChildUI	(CUIBase* pChildUI);

		void Clear();

		void MouseOnCheck();
		void UpdatePosition();

		__inline void SetLocalPosition(const Maths::Vector2& pos)	{ m_vecPos = pos;				}
		 void SetScale(const Maths::Vector2& size)					{ m_vecSize = size;				}
		 void SetFullScreen(bool state)								{ m_bFullScreen = state;		}
		 void SetParent(CUIBase* pParent)							{ m_pParent = pParent;			}
		 void SetIndex(INT index)									{ m_iIndex = index;				}

		__inline void SetChangeHierarchy(bool state)				{ m_bChangeHierarchy = state;	}
		__inline void SetType(Enums::eUIType type)					{ m_eType = type;				}
		__inline void SetDrag(bool state)							{ m_bDraggable = state;			}
		__inline void SetWorldObject(bool state)					{ m_bWorldObject = state;		}


		__inline bool					GetFullScreen()		const { return m_bFullScreen;			}
		__inline bool					GetEnable()			const { return m_bEnable;				}
		__inline Enums::eUILayer		GetLayer()			const { return m_eLayerType;			}
		__inline Enums::eUIType			GetType()			const { return m_eType;					}
		__inline bool					GetDraggable()		const { return m_bDraggable;			}
		__inline bool					GetDragging()		const { return m_bIsDrag;				}
		__inline bool					GetWorldObject()	const { return m_bWorldObject;			}
		__inline bool					GetChangeHierarchy()const { return m_bChangeHierarchy;		}
		__inline bool					GetPrevOn()			const { return m_bPrevMouseOn;			}
		__inline bool					GetPrevDown()		const { return m_bPrevMouseDown;		}
		__inline bool					GetCurOn()			const { return m_bCurMouseOn;			}
		__inline bool					GetFocus()			const { return m_bFocusOn;				}
		__inline INT					GetIndex()			const { return m_iIndex;				}
		__inline CUIBase*				GetParent()			const { return m_pParent;				}

		__inline const std::vector<CUIBase*>&GetChilds()	const { return m_vecChilds;				}


		__inline const Maths::Vector2& GetWorldPosition()	const { return m_vecRenderPos;			}
		__inline const Maths::Vector2& GetLocalPosition()	const { return m_vecPos;				}
		__inline const Maths::Vector2& GetScale()			const { return m_vecSize;				}

#pragma region  Basic Event
		void Initialize();
		void Release();

		void Tick();
		void LastTick();

		void Render(HDC hdc) const;
#pragma endregion

#pragma region State Event
		void Active();
		void InActive();

#pragma endregion

#pragma region  UI Event
		void Over();

		void Enter();
		void Exit();

		void Down();
		void Up();
#pragma endregion


	protected:

		Maths::Vector2 m_vecRenderPos;

	private:


#pragma region Virtual
		virtual void OnInitialize();
		virtual void OnRelease();

		virtual void OnActive();
		virtual void OnInActive();

		virtual void OnTickComponent();
		virtual void OnLastTickComponent();

		virtual void OnRender(HDC hdc) const;
		virtual void OnClear();

		virtual void OnEnter();
		virtual void OnExit();

		virtual void OnDown();
		virtual void OnUp();

		virtual void OnClick();
#pragma endregion


		CUIBase*	m_pParent;
		INT			m_iIndex;

		bool		m_bFullScreen;
		bool		m_bEnable;

		bool		m_bDraggable;
		bool		m_bIsDrag;

		bool		m_bWorldObject;
		bool		m_bChangeHierarchy;

		bool		m_bPrevMouseOn;
		bool		m_bCurMouseOn;

		bool		m_bPrevMouseDown;
		bool		m_bCurMouseDown;

		bool		m_bFocusOn;


		Enums::eUIType			m_eType;
		Enums::eUILayer			m_eLayerType;

		Maths::Vector2			m_vecPos;
		Maths::Vector2			m_vecSize;
		Maths::Vector2			m_vecDragStartPos;

		std::vector<CUIBase*>	m_vecChilds;

	};
}


