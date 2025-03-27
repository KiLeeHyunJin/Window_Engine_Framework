#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CUIManager.h"
#include "CCollisionManager.h"
#include "CInputManager.h"

#include "CRenderer.h"

namespace Framework
{
	HWND CRenderManager::m_hWnd			= nullptr;
	HDC CRenderManager::m_hDC			= nullptr;

	HDC CRenderManager::m_BackHDC		= nullptr;
	HBITMAP CRenderManager::m_BmpBuffer = nullptr;


	Maths::Vector2 CRenderManager::m_vecWinSize				= Maths::Vector2::Zero;
	Maths::Vector2 CRenderManager::m_vecCurrentBufferSize	= Maths::Vector2::Zero;
	Maths::Vector2 CRenderManager::m_vecScreenSize			= Maths::Vector2::Zero;

	DWORD CRenderManager::m_winStyle = 0;
	bool CRenderManager::m_bScreenState = false;


	CRenderManager::CRenderManager()
	{}
	CRenderManager::~CRenderManager()
	{}

	void CRenderManager::DrawRectangle(HDC hdc, const Maths::Vector2& position, const Maths::Vector2& scale)
	{
		Rectangle(hdc,
			(UINT)(position.x - (scale.x * 0.5f)),
			(UINT)(position.y - (scale.y * 0.5f)),
			(UINT)(position.x + (scale.x * 0.5f)),
			(UINT)(position.y + (scale.y * 0.5f)));
	}

	void CRenderManager::DrawEllipse(HDC hdc, const Maths::Vector2& position, const Maths::Vector2& scale)
	{
		Ellipse(hdc,
			(UINT)(position.x - (scale.x * 0.5f)),
			(UINT)(position.y - (scale.y * 0.5f)),
			(UINT)(position.x + (scale.x * 0.5f)),
			(UINT)(position.y + (scale.y * 0.5f)));
	}

	void CRenderManager::DrawWText(HDC hdc, int x, int y, const std::wstring& text)
	{
		const int INT = (int)wcsnlen_s(text.c_str(), 50);
		TextOut(hdc, 0, 15, text.c_str(), INT);
	}

	void CRenderManager::Initialize(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen)
	{
		CRenderManager::AdjustWindow(hWnd, width, height, xPos, yPos, winStyle, menu);
		m_BackHDC = CreateCompatibleDC(m_hDC);
		ChangeScreenSize(screen);
	}

	void CRenderManager::Release()
	{
	}

	void CRenderManager::Render()
	{
		BeginDraw();

		SCENE::Render(m_BackHDC);
		UI::Render(m_BackHDC);
		COLLISION::Render(m_BackHDC);

		TIME::Render(m_BackHDC);

		INPUT::Render(m_BackHDC, 300, 300);

		EndDraw();
	}

	void CRenderManager::BeginDraw()
	{
		Rectangle(m_BackHDC, -1, -1, (int)m_vecCurrentBufferSize.x + 1, (int)m_vecCurrentBufferSize.y + 1);
	}

	void CRenderManager::EndDraw()
	{
		BitBlt(
			m_hDC, 0, 0, (int)m_vecCurrentBufferSize.x, (int)m_vecCurrentBufferSize.y,
			m_BackHDC, 0, 0, SRCCOPY);
	}

	void CRenderManager::AdjustWindow(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu)
	{
		m_hWnd = hWnd;
		m_hDC = GetDC(m_hWnd);

		m_vecWinSize.x = (float)width;
		m_vecWinSize.y = (float)height;
		m_winStyle = winStyle;

		m_vecScreenSize.x = (float)GetSystemMetrics(SM_CXSCREEN);
		m_vecScreenSize.y = (float)GetSystemMetrics(SM_CYSCREEN);

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, m_winStyle, false);

		int adjustedWidth = rect.right - rect.left;
		int adjustedHeight = rect.bottom - rect.top;

		SetWindowPos(m_hWnd, nullptr, 
			xPos - rect.left, yPos - rect.top, 
			adjustedWidth, adjustedHeight, 
			SWP_NOZORDER | SWP_NOACTIVATE);

		ShowWindow(m_hWnd, SW_SHOW);
	}

	void CRenderManager::ChangeScreenSize(bool maximumScale)
	{	
		m_bScreenState = maximumScale;

		if (maximumScale)
		{
			m_vecCurrentBufferSize = m_vecScreenSize;
		}
		else
		{
			m_vecCurrentBufferSize = m_vecWinSize;
		}

		RECT rect = { 0, 0, (LONG)m_vecCurrentBufferSize.x, (LONG)m_vecCurrentBufferSize.y };
		int xPos, yPos = 0;

		AdjustWindowRect(&rect, m_winStyle, false);

		if (maximumScale)
		{
			xPos = 0;
			yPos = 0;
		}
		else
		{
			xPos = ((int)(m_vecScreenSize.x - m_vecCurrentBufferSize.x) >> 1) - rect.left;
			yPos = ((int)(m_vecScreenSize.y - m_vecCurrentBufferSize.y) >> 1) - rect.top;
		}

		const int adjustedWidth  = (rect.right - rect.left);
		const int adjustedHeight = (rect.bottom - rect.top);

		SetWindowPos(m_hWnd, nullptr, 
			xPos, yPos , 
			adjustedWidth, adjustedHeight, 
			SWP_NOZORDER | SWP_NOACTIVATE);

		//SetWindowPos(m_hWnd, NULL,
		//	xPos, yPos,
		//	m_iCurrentBufferBitmapWidth, m_iCurrentBufferBitmapHeight,
		//	0);
		CreateBackBuffer((int)m_vecCurrentBufferSize.x, (int)m_vecCurrentBufferSize.y);

		Renderer::CRenderer::SetResolution(m_vecCurrentBufferSize);
	}

	void CRenderManager::CreateBackBuffer(int width, int height)
	{
		m_BmpBuffer = CreateCompatibleBitmap(m_hDC, width, height);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(m_BackHDC, m_BmpBuffer);
		DeleteObject(oldBitmap);
	}
}