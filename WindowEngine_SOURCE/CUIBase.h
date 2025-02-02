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
		
		void SetFullScreen(bool state) { m_bFullScreen = state; }


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
	};
}

