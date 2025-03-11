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

		Maths::Vector2 GetResolution() const 
		{ 
			return  Maths::Vector2(
				(float)CRenderManager::m_iCurrentBufferBitmapWidth, 
				(float)CRenderManager::m_iCurrentBufferBitmapHeight); 
		}

		HDC GetHDC() const							{ return CRenderManager::GetHDC(); }
		__forceinline bool GetScreenState() const	{ return CRenderManager::m_bScreenState; };
		__forceinline HWND GetHWND() const			{ return CRenderManager::m_hWnd; }

	private:
		void Tick();
		void LastTick();
		//void Destroy();
		void Render();
		bool m_bRelease;
	};

}

