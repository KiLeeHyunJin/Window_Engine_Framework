#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CUIManager.h"
#include "CCollisionManager.h"
#include "CInputManager.h"
#include "CObjectManager.h"

#include "CRenderer.h"

namespace Framework
{

	namespace Manager
	{
		HWND CRenderManager::m_hWnd = nullptr;
		HDC CRenderManager::m_hDC = nullptr;

		HDC CRenderManager::m_BackHDC = nullptr;
		HBITMAP CRenderManager::m_BmpBuffer = nullptr;


		Maths::Vector2Int CRenderManager::m_vecWinSize = Maths::Vector2::Zero;
		Maths::Vector2Int CRenderManager::m_vecCurrentBufferSize = Maths::Vector2::Zero;
		Maths::Vector2Int CRenderManager::m_vecScreenSize = Maths::Vector2::Zero;

		DWORD CRenderManager::m_winStyle = 0;
		bool CRenderManager::m_bScreenState = false;


		CRenderManager::CRenderManager()
		{
		}
		CRenderManager::~CRenderManager()
		{
		}


		void CRenderManager::Initialize(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen)
		{
			CRenderManager::AdjustWindow(hWnd, width, height, xPos, yPos, winStyle, menu);
			m_BackHDC = CreateCompatibleDC(m_hDC); //DC생성
			ChangeScreenSize(screen); //윈도우 크기 변경 및 비트맵 생성
		}

		void CRenderManager::Release()
		{
		}

		void CRenderManager::Render()
		{
			BeginDraw();

			SCENE::Render(m_BackHDC);
			OBJECT::Render(m_BackHDC);

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
				m_hDC, //출력
				0, 0,  //Start
				(int)m_vecCurrentBufferSize.x, (int)m_vecCurrentBufferSize.y, //Size

				m_BackHDC, //복사내용
				0, 0, //Start
				SRCCOPY);
			//흰색으로 밀어버린다.
			PatBlt(m_BackHDC, -1, -1, (int)m_vecCurrentBufferSize.x + 1, (int)m_vecCurrentBufferSize.y + 1, WHITENESS);
		}

		void CRenderManager::AdjustWindow(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu)
		{
			m_hWnd = hWnd;
			m_hDC = GetDC(m_hWnd);

			m_vecWinSize.x = width;
			m_vecWinSize.y = height;
			m_winStyle = winStyle;

			m_vecScreenSize.x = GetSystemMetrics(SM_CXSCREEN);
			m_vecScreenSize.y = GetSystemMetrics(SM_CYSCREEN);

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

			const int adjustedWidth = (rect.right - rect.left);
			const int adjustedHeight = (rect.bottom - rect.top);

			SetWindowPos(m_hWnd, nullptr,
				xPos, yPos,
				adjustedWidth, adjustedHeight,
				SWP_NOZORDER | SWP_NOACTIVATE);


			//새로운 사이즈의 비트맵 생성
			CreateBackBuffer((int)m_vecCurrentBufferSize.x, (int)m_vecCurrentBufferSize.y);

			//Renderer::CRenderer::SetResolution(m_vecCurrentBufferSize);
		}

		void CRenderManager::CreateBackBuffer(int width, int height)
		{
			m_BmpBuffer = CreateCompatibleBitmap(m_hDC, width, height);
			HBITMAP oldBitmap = (HBITMAP)SelectObject(m_BackHDC, m_BmpBuffer);
			DeleteObject(oldBitmap);
		}
	}

	
}