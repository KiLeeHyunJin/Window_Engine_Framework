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

		void Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu);
		void Release();
		Maths::Vector2 GetResolution() const 
		{ 
			return  Maths::Vector2(
				CRenderManager::m_iCurrentBufferBitmapWidth, 
				CRenderManager::m_iCurrentBufferBitmapHeight); 
		}
		HDC GetHDC() const { return CRenderManager::GetHDC(); }
	private:
		void Tick();
		void LastTick();

		void Render();
	};

}

