#include "CApplication.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"

namespace Framework
{
	CApplication::CApplication() :
		m_hWnd(nullptr),	m_hDC(nullptr),
		m_BackHDC(nullptr), m_BmpBuffer(nullptr),
		m_iWindowWidth(0),	m_iWindowHeight(0),
		m_iScreenWidth(0),	m_iScreenHeight(0),
		m_iCurrentBufferBitmapWidth(0), 
		m_iCurrentBufferBitmapHeight(0),
		m_bScreenMaximum(false)
	{
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu)
	{
		AdjustWindow(hWnd, width, height, xPos, yPos, winStyle, menu);
		m_BackHDC = CreateCompatibleDC(m_hDC);

		CreateBackBuffer(width, height);
		INPUT::Initialize();
		TIME::Initialize();
		SCENE::Initialize();
	}

	void CApplication::AdjustWindow(HWND hWnd, int width, int height,int xPos, int yPos, DWORD winStyle, bool menu)
	{
		m_hWnd = hWnd;
		m_hDC = GetDC(m_hWnd);

		m_iWindowWidth = width;
		m_iWindowHeight = height;

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, winStyle, false);
		SetWindowPos(m_hWnd, nullptr, xPos, yPos, ((int)width), ((int)height), 0);
		ShowWindow(m_hWnd, true);

		m_iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		m_iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	}

	void CApplication::CreateBackBuffer(int width, int height)
	{
		HBITMAP newBmpBuffer = CreateCompatibleBitmap(m_hDC, width, height);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(m_BackHDC, newBmpBuffer);
		DeleteObject(oldBitmap);
		m_BmpBuffer = newBmpBuffer;
	}

	void CApplication::Release()
	{
		SCENE::Release();
	}

	void CApplication::Run()
	{
		Tick();
		LastTick();
		Render();
	}

	void CApplication::Tick()
	{
		INPUT::Tick();
		TIME::Tick();
		SCENE::Tick();
	}

	void CApplication::LastTick()
	{
		SCENE::LastTick();
	}

	void CApplication::Render()
	{
		BeginDraw();
		SCENE::Render(m_BackHDC);
		TIME::Render(m_BackHDC);
		EndDraw();
	}

	void CApplication::BeginDraw()
	{
		if (m_bScreenMaximum)
		{
			if (m_iCurrentBufferBitmapWidth != m_iScreenWidth)
			{
				m_iCurrentBufferBitmapWidth		= m_iScreenWidth;
				m_iCurrentBufferBitmapHeight	= m_iScreenHeight;
			}
		}
		else
		{
			if (m_iCurrentBufferBitmapWidth != m_iWindowWidth)
			{
				m_iCurrentBufferBitmapWidth		= m_iWindowWidth;
				m_iCurrentBufferBitmapHeight	= m_iWindowHeight;
			}
		}
		Rectangle(m_BackHDC, -1, -1, m_iCurrentBufferBitmapWidth + 1, m_iCurrentBufferBitmapHeight + 1);
	}

	void CApplication::EndDraw()
	{
		BitBlt(
			m_hDC, 0, 0, m_iCurrentBufferBitmapWidth, m_iCurrentBufferBitmapHeight,
			m_BackHDC, 0, 0, SRCCOPY);
	}

	void CApplication::ChangeScreenSize(bool maximumScale)
	{
		int width, height;
		m_bScreenMaximum = maximumScale;
		if (m_bScreenMaximum)
		{
			width	= m_iScreenWidth;
			height	= m_iScreenHeight;
			SetWindowPos(m_hWnd, NULL,
				0, 0,
				m_iScreenWidth, m_iScreenHeight,
				0);
		}
		else
		{
			width	= m_iWindowWidth;
			height	= m_iWindowHeight;
			SetWindowPos(m_hWnd, NULL,
				(m_iScreenWidth  - m_iWindowWidth)  >> 1,
				(m_iScreenHeight - m_iWindowHeight) >> 1,
				m_iWindowWidth, m_iWindowHeight,
				0);
		}

		CreateBackBuffer(width, height);
	}

}






































