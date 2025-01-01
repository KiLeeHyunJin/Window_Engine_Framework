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


		int m_iWindowWidth;	//â��� ������
		int m_iWindowHeight;

		int m_iScreenWidth; //ȭ�� �ػ�
		int m_iScreenHeight;

		int m_iCurrentBufferBitmapWidth;
		int m_iCurrentBufferBitmapHeight;

		bool m_bScreenMaximum;

	};

}

