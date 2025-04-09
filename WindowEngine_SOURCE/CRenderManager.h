#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;

	namespace Manager
	{
		class CRenderManager
		{
			DECLARE_SINGLE(CRenderManager)
			RELEASE_SINGLE
		public:

			__forceinline const Maths::Vector2Int& GetResolution() { return m_vecCurrentBufferSize; }

			friend CApplication;
		private:
			//CRenderManager();
			~CRenderManager();
			void Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen);
			void Release();

			void Render();

			void BeginDraw();
			void EndDraw();

			void AdjustWindow(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu);
			void ChangeScreenSize(bool maximumScale);

			void CreateBackBuffer(int width, int height);

			HDC GetHDC() const  { return m_hDC; }

			HWND m_hWnd									= {};
			HDC m_hDC									= {};

			HDC m_BackHDC								= {};
			HBITMAP m_BmpBuffer							= {};

			Maths::Vector2Int m_vecWinSize				= {};
			Maths::Vector2Int m_vecCurrentBufferSize	= {};
			Maths::Vector2Int m_vecScreenSize			= {};

			DWORD m_winStyle							= {};
			bool m_bScreenState							= {};
		};
	}

	
	using RENDER = Manager::CRenderManager;
//#define RENDER CRenderManager

}

