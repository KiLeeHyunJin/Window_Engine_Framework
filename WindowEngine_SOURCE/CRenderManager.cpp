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
		CRenderManager* CRenderManager::s_instance = nullptr;


		CRenderManager::~CRenderManager()
		{
		}


		void CRenderManager::Initialize(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen)
		{
			CRenderManager::AdjustWindow(hWnd, width, height, xPos, yPos, winStyle, menu);
			m_CompleteHDC	= CreateCompatibleDC(m_hDC); //DC생성
			m_DrawHDC		= CreateCompatibleDC(m_hDC); //DC생성

			ChangeScreenSize(screen); //윈도우 크기 변경 및 비트맵 생성

			PatBlt(m_CompleteHDC, -1, -1, (int)m_vecCurrentBufferSize.x + 1, (int)m_vecCurrentBufferSize.y + 1, WHITENESS);
			PatBlt(m_DrawHDC	, -1, -1, (int)m_vecCurrentBufferSize.x + 1, (int)m_vecCurrentBufferSize.y + 1, WHITENESS);
		}

		void CRenderManager::Release()
		{
		}

		void CRenderManager::Render()
		{
			GET_SINGLE(SCENE).Render(m_DrawHDC);
			GET_SINGLE(OBJECT).Render(m_DrawHDC);

			GET_SINGLE(UI).Render(m_DrawHDC);

			GET_SINGLE(COLLISION).Render(m_DrawHDC);

			GET_SINGLE(TIME).Render(m_DrawHDC);
			GET_SINGLE(INPUT).Render(m_DrawHDC, 300, 300);

			//전부 그렸으니 버퍼 교체
			std::swap(m_CompleteHDC, m_DrawHDC);

			Draw();

			//그려넣을 DC를 흰색으로 초기화
			PatBlt(m_DrawHDC, -1, -1, (int)m_vecCurrentBufferSize.x + 1, (int)m_vecCurrentBufferSize.y + 1, WHITENESS);

		}

		void CRenderManager::Draw() const
		{
			//완성된 DC를 출력
			BitBlt(
				m_hDC, //출력
				0, 0,  //Start
				(int)m_vecCurrentBufferSize.x, (int)m_vecCurrentBufferSize.y, //Size

				m_DrawHDC, //복사내용
				0, 0, //Start
				SRCCOPY);
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

		}

		void CRenderManager::CreateBackBuffer(int width, int height) const
		{
			HBITMAP m_BmpBuffer		= CreateCompatibleBitmap(m_hDC, width, height);
			HBITMAP m_BmpBuffer2	= CreateCompatibleBitmap(m_hDC, width, height);

			HBITMAP oldBitmap		= (HBITMAP)SelectObject(m_DrawHDC,		m_BmpBuffer);
			HBITMAP oldBitmap2		= (HBITMAP)SelectObject(m_CompleteHDC,	m_BmpBuffer2);

			DeleteObject(oldBitmap);
			DeleteObject(oldBitmap2);
		}
		IWICImagingFactory* CRenderManager::GetImageFactory()
		{
			return nullptr;
		}
		ID2D1HwndRenderTarget* CRenderManager::GetRenderTarget()
		{
			return nullptr;
		}
		void CRenderManager::SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlignment)
		{
		}
		void CRenderManager::SetTextParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment)
		{
		}
		void CRenderManager::Text(const std::wstring& str, const Maths::Vector2& startPoint, const Maths::Vector2& endPoint)
		{
		}
		void CRenderManager::Text(const std::wstring& str, const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color, float fontSize)
		{
		}
		void CRenderManager::Text(const std::wstring& str, float dstX, float dstY, float dstW, float dstH)
		{
		}
		void CRenderManager::Text(const std::wstring& str, float dstX, float dstY, float dstW, float dstH, const Color& color, float fontSize)
		{
		}
		void CRenderManager::Line(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint)
		{
		}
		void CRenderManager::Line(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color, float strokeWidth)
		{
		}
		void CRenderManager::FrameRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, float strokeWidth)
		{
		}
		void CRenderManager::FrameRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color, float strokeWidth)
		{
		}
		void CRenderManager::FillRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint)
		{
		}
		void CRenderManager::FillRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color)
		{
		}
		void CRenderManager::FrameEllipse(const Maths::Vector2& startPoint, float radius, float strokeWidth)
		{
		}
		void CRenderManager::FrameEllipse(const Maths::Vector2& startPoint, float radius, const Color& color, float strokeWidth)
		{
		}
		void CRenderManager::FillEllipse(const Maths::Vector2& startPoint, float radius)
		{
		}
		void CRenderManager::FillEllipse(const Maths::Vector2& startPoint, float radius, const Color& color)
		{
		}
		void CRenderManager::FrameCircle(const Maths::Vector2& startPoint, float radius)
		{
		}
		void CRenderManager::FrameCircle(const Maths::Vector2& startPoint, float radius, const Color& color, float strokeWidth)
		{
		}
		void CRenderManager::FillCircle(const Maths::Vector2& startPoint, float radius)
		{
		}
		void CRenderManager::FillCircle(const Maths::Vector2& startPoint, float radius, const Color& color)
		{
		}
		void CRenderManager::Image(Resource::CSprite* pImg, const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, float alpha)
		{
		}
		void CRenderManager::FrameImage(Resource::CSprite* pImg, const Maths::Vector2& drawStartPoint, const Maths::Vector2& drawEndPoint, const Maths::Vector2& sliceStartPoint, const Maths::Vector2& sliceEndPoint, float alpha)
		{
		}
}


}