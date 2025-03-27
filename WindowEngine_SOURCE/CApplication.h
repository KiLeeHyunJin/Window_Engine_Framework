#pragma once
#include "CommonInclude.h"
#include "CRenderManager.h"
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

		__forceinline const Maths::Vector2& GetResolution() const { return  RENDER::m_vecCurrentBufferSize;	}

		__forceinline HDC GetHDC() const			{ return CRenderManager::GetHDC(); }
		__forceinline bool GetScreenState() const	{ return CRenderManager::m_bScreenState; };
		__forceinline HWND GetHWND() const			{ return CRenderManager::m_hWnd; }

	private:
		void Tick();
		void LastTick();
		//void Destroy();
		void Render();
		HWND m_hwnc;
		HDC m_hdc;
		//bool m_bRelease;
	};

}

