#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;




	class CRenderManager
	{
	public:
		static void DrawRectangle(HDC hdc, Maths::Vector2 position, Maths::Vector2 scale);
		static void DrawEllipse(HDC hdc, Maths::Vector2 position, Maths::Vector2 scale);
		static void DrawWText(HDC hdc, int x, int y, std::wstring& text);

		friend CApplication;
	private:
		CRenderManager();
		~CRenderManager();
		static void Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen);
		static void Release();

		static void Render();

		static void BeginDraw();
		static void EndDraw();

		static void AdjustWindow(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu);
		static void ChangeScreenSize(bool maximumScale);

		static void CreateBackBuffer(int width, int height);

		inline static HDC GetHDC() { return m_hDC; }

		static HWND m_hWnd;
		static HDC m_hDC;

		static HDC m_BackHDC;
		static HBITMAP m_BmpBuffer;

		static int m_iWindowWidth;	//창모드 사이즈
		static int m_iWindowHeight;

		static int m_iScreenWidth; //화면 해상도
		static int m_iScreenHeight;

		static int m_iCurrentBufferBitmapWidth;
		static int m_iCurrentBufferBitmapHeight;

		static bool m_bScreenState;
	};
	using RENDER = CRenderManager;
//#define RENDER CRenderManager

}

