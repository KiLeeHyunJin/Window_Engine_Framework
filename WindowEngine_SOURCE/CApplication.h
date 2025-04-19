#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication
	{
	public:
		CApplication();
		virtual ~CApplication();

		void Run();
		void ChangeScreenSize(bool maximumScale);

		void Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen = false);
		void Release();

		//const Maths::Vector2& GetResolution();

		HDC GetHDC() const			;
		bool GetScreenState() const	;
		HWND GetHWND() const		;

	private:
		void Tick();
		void LastTick();
		void FixedTick();
		//void Destroy();
		void Render();
		HWND m_hwnc;
		HDC m_hdc;
		//bool m_bRelease;
	};

}

