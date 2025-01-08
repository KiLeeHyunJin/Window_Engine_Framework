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

		void Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu);
		void Release();
		Maths::Vector2 GetResolution() const { return  Maths::Vector2(m_iCurrentBufferBitmapWidth, m_iCurrentBufferBitmapHeight); }
		HDC GetHDC() const { return m_hDC; }
	private:
		void Tick();
		void LastTick();

		void Render();

		void BeginDraw() const;
		void EndDraw() const;

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

		int m_iCurrentBufferBitmapWidth;
		int m_iCurrentBufferBitmapHeight;

	};

}

