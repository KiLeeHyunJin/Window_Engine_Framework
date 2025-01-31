#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CCollisionManager.h"
#include "CRenderer.h"

namespace Framework
{
	HWND CRenderManager::m_hWnd			= nullptr;
	HDC CRenderManager::m_hDC			= nullptr;

	HDC CRenderManager::m_BackHDC		= nullptr;
	HBITMAP CRenderManager::m_BmpBuffer = nullptr;

	int CRenderManager::m_iWindowWidth	= 0;	//창모드 사이즈
	int CRenderManager::m_iWindowHeight = 0;

	int CRenderManager::m_iScreenWidth	= 0; //화면 해상도
	int CRenderManager::m_iScreenHeight = 0;

	int CRenderManager::m_iCurrentBufferBitmapWidth		= 0;
	int CRenderManager::m_iCurrentBufferBitmapHeight	= 0;

	bool CRenderManager::m_bScreenState = false;


	CRenderManager::CRenderManager()
	{}
	CRenderManager::~CRenderManager()
	{}

	void CRenderManager::DrawRectangle(HDC hdc, UINT left, UINT top, UINT right, UINT bottom)
	{
	}
	void CRenderManager::DrawEllipse(HDC hdc, UINT left, UINT top, UINT right, UINT bottom)
	{

	}
	void CRenderManager::DrawWText(HDC hdc, int x, int y, std::wstring& text)
	{

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
		TIME::Render(m_BackHDC);
		COLLISION::Render(m_BackHDC);
		EndDraw();
	}

	void CRenderManager::BeginDraw()
	{
		Rectangle(m_BackHDC, -1, -1, m_iCurrentBufferBitmapWidth + 1, m_iCurrentBufferBitmapHeight + 1);
	}

	void CRenderManager::EndDraw()
	{
		BitBlt(
			m_hDC, 0, 0, m_iCurrentBufferBitmapWidth, m_iCurrentBufferBitmapHeight,
			m_BackHDC, 0, 0, SRCCOPY);
	}

	void CRenderManager::AdjustWindow(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu)
	{
		m_hWnd = hWnd;
		m_hDC = GetDC(m_hWnd);

		m_iWindowWidth = width;
		m_iWindowHeight = height;

		m_iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		m_iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect(&rect, winStyle, false);
		SetWindowPos(m_hWnd, nullptr, xPos, yPos, ((int)width), ((int)height), 0);
		ShowWindow(m_hWnd, true);
	}

	void CRenderManager::ChangeScreenSize(bool maximumScale)
	{
		m_bScreenState = maximumScale;
		int xPos, yPos;
		if (maximumScale)
		{
			m_iCurrentBufferBitmapWidth = m_iScreenWidth;
			m_iCurrentBufferBitmapHeight = m_iScreenHeight;

			xPos = 0;
			yPos = 0;
		}
		else
		{
			m_iCurrentBufferBitmapWidth = m_iWindowWidth;
			m_iCurrentBufferBitmapHeight = m_iWindowHeight;

			xPos = (m_iScreenWidth - m_iWindowWidth)	>> 1;
			yPos = (m_iScreenHeight - m_iWindowHeight)	>> 1;
		}

		SetWindowPos(m_hWnd, NULL,
			xPos, yPos,
			m_iCurrentBufferBitmapWidth, m_iCurrentBufferBitmapHeight,
			0);
		CreateBackBuffer(m_iCurrentBufferBitmapWidth, m_iCurrentBufferBitmapHeight);

		Maths::Vector2 resolution(m_iCurrentBufferBitmapWidth, m_iCurrentBufferBitmapHeight);
		Renderer::CRenderer::SetResolution(resolution);
	}

	void CRenderManager::CreateBackBuffer(int width, int height)
	{
		m_BmpBuffer = CreateCompatibleBitmap(m_hDC, width, height);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(m_BackHDC, m_BmpBuffer);
		DeleteObject(oldBitmap);
	}
}