#pragma once
#include "CUIBase.h"
//#include "CTexture.h"

//#include "CRenderManager.h"
#include "Structs.h"

namespace Framework
{
	class CUIManager;

	class CButton :
		public CUIBase
	{
	public:
		CButton();
		virtual ~CButton();

#pragma region Button Add Event
		template<typename T>
		void AddOnClickDelegate(T* owner, void(T::* func)())
		{
			m_pOnClick = [owner, func]()
				{		(owner->*func)();		};
		}

		template<typename T>
		void AddOnDownDelegate(T* owner, void(T::* func)())
		{
			m_pOnDown = [owner, func]()
				{		(owner->*func)();		};
		}
		template<typename T>
		void AddOnUpDelegate(T* owner, void(T::* func)())
		{
			m_pOnUp = [owner, func]()
				{		(owner->*func)();		};
		}

		void AddOnClickDelegate(std::function<void()> func)
		{
			m_pOnClick = func;
		}

		void AddOnDownDelegate(std::function<void()> func)
		{
			m_pOnDown = func;
		}

		void AddOnUpDelegate(std::function<void()> func)
		{
			m_pOnUp = func;
		}
#pragma endregion

	
	private:
		virtual void OnInitialize()				override;
		virtual void OnRelease()				override;

		virtual void OnActive()					override;
		virtual void OnInActive()				override;
		
		virtual void OnTick()					override;
		virtual void OnLastTick()				override;
		
		virtual void OnClear()					override;
		virtual void OnRender(HDC hdc) const	override;


		virtual void OnDown()					override;
		virtual void OnUp()						override;

		virtual void OnEnter()					override;
		virtual void OnExit()					override;

		void OnClick();

		std::function<void(void)> m_pOnClick = nullptr;
		std::function<void(void)> m_pOnDown = nullptr;
		std::function<void(void)> m_pOnUp = nullptr;

		float			m_fClickSumTime = 0;

		Color m_colorFill						= {};
		


	};


}

