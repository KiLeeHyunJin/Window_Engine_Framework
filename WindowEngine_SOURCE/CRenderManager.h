#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;

	namespace Manager
	{
		class CRenderManager
		{
		public:

			__forceinline static const Maths::Vector2Int& GetResolution() { return m_vecCurrentBufferSize; }

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

			static HDC GetHDC() { return m_hDC; }

			static HWND m_hWnd;
			static HDC m_hDC;

			static HDC m_BackHDC;
			static HBITMAP m_BmpBuffer;

			static Maths::Vector2Int m_vecWinSize;
			static Maths::Vector2Int m_vecCurrentBufferSize;
			static Maths::Vector2Int m_vecScreenSize;

			static DWORD m_winStyle;
			static bool m_bScreenState;
		};
	}

	
	using RENDER = Manager::CRenderManager;
//#define RENDER CRenderManager

}

