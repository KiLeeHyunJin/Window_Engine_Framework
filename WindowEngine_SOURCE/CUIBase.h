#pragma once
#include "CEntity.h"
#include "CommonInclude.h"
#include "CSprite.h"

namespace Framework
{
	namespace Manager
	{
		class CUIManager;
	}
	using namespace Resource;
	using namespace Maths;
	using namespace Enums;

	class CUIBase : public CEntity
	{
	public :
		enum class eUIState
		{
			Default,
			Hovered,
			Pressed,
			Clicked,
			Size,
		};
	public:
		CUIBase();
		virtual ~CUIBase();

		void AddChildUI		(CUIBase* pChildUI);
		void RemoveChildUI	(CUIBase* pChildUI);

		void Clear();

		//void MouseOnCheck();
		void UpdatePosition();

		__inline void SetLocalPosition(const Vector2& pos)			{ m_vecPos = pos;					}
		 void SetScale(const Vector2& size)							{ m_vecSize = size;					}
		 void SetFullScreen(bool state)								{ m_bFullScreen = state;			}
		 void SetParent(CUIBase* pParent)							{ m_pParent = pParent;				}
		 void SetIndex(INT index)									{ m_iIndex = index;					}
		 void SetCurrentSprite(const CSprite* sprite)				{ m_pCurrentSprite = sprite;		}
		 void SetSprite(const CSprite* sprite, eUIState state)		{ m_pSprites[(INT)state] = sprite;	}
		 void SetState(eUIState state)								{ m_eCurrState = state;		m_pCurrentSprite = m_pSprites[(int)state]; }


		__inline void SetChangeHierarchy(bool state)				{ m_bChangeHierarchy = state;		}
		__inline void SetType(Enums::eUIType type)					{ m_eType = type;					}
		__inline void SetDraggable(bool state)							{ m_bDraggable = state;				}
		__inline void SetWorldObject(bool state)					{ m_bWorldObject = state;			}

		__inline const CSprite*					GetSprite(eUIState state)	const { return m_pSprites[(INT)state];	}
		__inline bool							GetFullScreen()				const { return m_bFullScreen;			}
		__inline bool							GetEnable()					const { return m_bEnable;				}
		__inline eUILayer						etLayer()					const { return m_eLayerType;			}
		__inline eUIType						GetType()					const { return m_eType;					}
		__inline bool							GetDraggable()				const { return m_bDraggable;			}
		__inline bool							GetDragging()				const { return m_bDraggable && m_eCurrState == eUIState::Pressed;				}
		__inline bool							GetWorldObject()			const { return m_bWorldObject;			}
		__inline bool							GetChangeHierarchy()		const { return m_bChangeHierarchy;		}
		__inline bool							GetPrevOn()					const { return m_ePrevState != eUIState::Default;			}
		__inline bool							GetPrevDown()				const { return m_ePrevState == eUIState::Pressed;			}
		__inline bool							GetCurrOn()					const { return m_bCurMouseOn;			}
		__inline bool							GetFocus()					const { return m_eCurrState != eUIState::Default;			}
		__inline INT							GetIndex()					const { return m_iIndex;				}
		__inline CUIBase*						GetParent()					const { return m_pParent;				}
	
		__inline const std::vector<CUIBase*>&	GetChilds()					const { return m_vecChilds;				}
		
		RECT GetRect();
		bool MouseInRect();

		__inline const Vector2& GetWorldPosition()							const { return m_vecRenderPos;			}
		__inline const Vector2& GetLocalPosition()							const { return m_vecPos;				}
		__inline const Vector2& GetScale()									const { return m_vecSize;				}

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
		//void Over();

		void Enter();
		void Exit();

		void Down();
		void Up();
#pragma endregion


	protected:

		Vector2 m_vecRenderPos;

	private:

#pragma region Virtual
		virtual void OnInitialize();
		virtual void OnRelease()							{ }
															  
		virtual void OnActive()								{ }
		virtual void OnInActive()							{ }
															  
		virtual void OnTick()								{ }
		virtual void OnLastTick()							{ }
															  
		virtual void OnRender(HDC hdc) const;				  
		virtual void OnClear()								{ }
															  
		virtual void OnEnter()								{ }
		virtual void OnExit()								{ }
															  
		virtual void OnDown()								{ }
		virtual void OnUp()									{ }
															  
		//virtual void OnClick()								{ }
#pragma endregion
		//Graphic
		const CSprite*  m_pCurrentSprite					=  nullptr;
		const CSprite*	m_pSprites[(int)eUIState::Size]		= {nullptr};

		//Property
		CUIBase*		m_pParent							=  nullptr;
		INT				m_iIndex							= -1;

		eUIType			m_eType								= eUIType::None;
		eUILayer		m_eLayerType						= eUILayer::None;

		//Transform
		Vector2			m_vecPos							= Vector2::Zero;
		Vector2			m_vecSize							= Vector2::Zero;
		Vector2			m_vecPrevMousePos = Vector2::Zero;
		//Vector2			m_vecDragStartPos					= Vector2::Zero;

		//State
		eUIState		m_eCurrState						= eUIState::Default;
		eUIState		m_ePrevState						= eUIState::Default;

		bool			m_bDraggable						= false;
		bool			m_bWorldObject						= false;
		bool			m_bChangeHierarchy					= false;

		bool			m_bFullScreen						= false;
		bool			m_bEnable							= false;

		bool			m_bCurMouseOn						= false;



		std::vector<CUIBase*>	m_vecChilds					= {};

	};
}


