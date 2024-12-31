#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class GameObject;

	class CApplication
	{
	public:
		CApplication();
		virtual ~CApplication();

		void Run();
		void ScreenSize(bool maximumScale);

		void Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu);

		void Release();

	private:
		void Tick();
		void LastTick();

		void Render();

		void BeginDraw();
		void EndDraw();

		void AdjustWindow(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu);
		void CreateBackBuffer(int width, int height);

		HWND m_hWnd;
		HDC m_hDC;

		HDC m_BackHDC;
		HBITMAP m_BmpBuffer;


		int m_iWindowWidth;	//창모드 사이즈
		int m_iWindowHeight;

		int m_iScreenWidth; //화면 해상도
		int m_iScreenHeight;

		int m_iCurrentWidth;
		int m_iCurrentHeight;

		bool m_bScreenMaximum;

	};

}

