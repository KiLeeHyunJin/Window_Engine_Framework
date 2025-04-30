#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CUIManager.h"
#include "CCollisionManager.h"
#include "CInputManager.h"
#include "CObjectManager.h"

#include "CRenderer.h"
#include "CCameraComponent.h"

#include "CSprite.h"


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
			CRenderManager::AdjustWindow(hWnd, WIN_SIZE_X, WIN_SIZE_Y, xPos, yPos, winStyle, menu);
			m_CompleteHDC	= CreateCompatibleDC(m_hDC); //DC생성
			m_DrawHDC		= CreateCompatibleDC(m_hDC); //DC생성

			CreateBackBuffer(WIN_SIZE_X, WIN_SIZE_Y);
			//ChangeScreenSize(screen); //윈도우 크기 변경 및 비트맵 생성

			//PatBlt(m_CompleteHDC, -1, -1, (int)m_vecCurrentBufferSize.x + 1, (int)m_vecCurrentBufferSize.y + 1, WHITENESS);
			//PatBlt(m_DrawHDC	, -1, -1, (int)m_vecCurrentBufferSize.x + 1, (int)m_vecCurrentBufferSize.y + 1, WHITENESS);

			HRESULT hResult;

			hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory); //D2D 팩토리 생성
			assert(S_OK == hResult && L"D2D1CreateFactory Create Failed");

			hResult = m_pFactory->CreateHwndRenderTarget	//윈도우 클라이언트 영역을 그리기 위한 RenderTarget생성
			(
				D2D1::RenderTargetProperties(),
				D2D1::HwndRenderTargetProperties
				(
					hWnd,
					D2D1::SizeU(WIN_SIZE_X, WIN_SIZE_Y),
					D2D1_PRESENT_OPTIONS_IMMEDIATELY
				),
				&m_pRenderTarget
			);
			assert(S_OK == hResult && L"HwnRenderTarget Create Failed");


			hResult = CoInitialize(nullptr);	//WICImagingFactory 생성
			assert(S_OK == hResult && L"CoInitialize Failed");

			hResult = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory)); //
			assert(S_OK == hResult && L"ImageFactory Create Failed");

			hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pWriteFactory), reinterpret_cast<IUnknown**>(&m_pWriteFactory));
			assert(S_OK == hResult && L"WriteFactory Create Failed");

			//텍스트 포맷 생성
			hResult = m_pWriteFactory->CreateTextFormat(
				L"굴림"
				, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
				10,
				L"ko", &m_pDefaultTextFormat);
			assert(S_OK == hResult && L"TextFormat Create Failed");

			hResult = m_pDefaultTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			assert(S_OK == hResult && L"TextFormat Set Alignment Failed");

			hResult = m_pDefaultTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			assert(S_OK == hResult && L"TextFormat SetParagraphAlignment Failed");

			//브러시 생성
			hResult = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(.0f, .0f, .0f), &m_pDefaultBrush);
			assert(S_OK == hResult && L"SolidColorBrush Create Failed");

			//텍스트 포맷 생성
			hResult = m_pWriteFactory->CreateTextFormat(
				L"굴림"
				, NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
				10,
				L"ko", &m_pCurTextFormat);
			assert(S_OK == hResult && L"TextFormat Create Failed");

			hResult = m_pCurTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
			assert(S_OK == hResult && L"TextFormat Set Alignment Failed");

			hResult = m_pCurTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			assert(S_OK == hResult && L"TextFormat SetParagraphAlignment Failed");

			//브러시 생성
			hResult = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(.0f, .0f, .0f), &m_pCurBrush);
			assert(S_OK == hResult && L"SolidColorBrush Create Failed");

			//IDWriteFactory* pDWriteFactory = nullptr;
			//DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));

			//HANDLE hFile = CreateFile(L"..//Resource//Font//HeirofLightRegular.ttf", GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
			//DWORD fileSize = GetFileSize(hFile, nullptr);
			//BYTE* fontData = new BYTE[fileSize];
			//DWORD bytesRead = 0;
			//::ReadFile(hFile, fontData, fileSize, &bytesRead, nullptr);
			//CloseHandle(hFile);

			//IDWriteFontFile* pFontFile = nullptr;
			//pDWriteFactory->CreateFontFileReference(
			//	L"..//Resource//Font//HeirofLightRegular.ttf",  // 파일 경로
			//	nullptr,          // 기본 NULL
			//	&pFontFile
			//);

			//IDWriteFontFace* pFontFace = nullptr;
			//pDWriteFactory->CreateFontFace(
			//	DWRITE_FONT_FACE_TYPE_TRUETYPE,
			//	1,
			//	&pFontFile,
			//	0,
			//	DWRITE_FONT_SIMULATIONS_NONE,
			//	&pFontFace
			//);

			//ID2D1SolidColorBrush* pBrush = nullptr;
			//m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pBrush);

		}

		void CRenderManager::Release()
		{

			if (m_pCurBrush != nullptr)
			{
				m_pCurBrush->Release();
				m_pCurBrush = nullptr;
			}

			if (m_pCurTextFormat != nullptr)
			{
				m_pCurTextFormat->Release();
				m_pCurTextFormat = nullptr;
			}

			if (m_pDefaultBrush != nullptr)
			{
				m_pDefaultBrush->Release();
				m_pDefaultBrush = nullptr;
			}

			if (m_pDefaultTextFormat != nullptr)
			{
				m_pDefaultTextFormat->Release();
				m_pDefaultTextFormat = nullptr;
			}

			if (m_pWriteFactory != nullptr)
			{
				m_pWriteFactory->Release();
				m_pWriteFactory = nullptr;
			}

			if (m_pImageFactory != nullptr)
			{
				m_pImageFactory->Release();
				m_pImageFactory = nullptr;
			}

			if (m_pRenderTarget != nullptr)
			{
				m_pRenderTarget->Release();
				m_pRenderTarget = nullptr;
			}

			if (m_pFactory != nullptr)
			{
				m_pFactory->Release();
				m_pFactory = nullptr;
			}
		}

		void CRenderManager::Render()
		{
			m_pRenderTarget->BeginDraw();
			FillRect(
				Maths::Vector2::Zero, 
				Maths::Vector2(WIN_SIZE_X, WIN_SIZE_Y),
				Color(255, 255, 255, 1));

			RenderCall();

			HRESULT hr = m_pRenderTarget->EndDraw();
			//if (hr == D2DERR_RECREATE_TARGET) 
			//{
			//}
			//전부 그렸으니 버퍼 교체
			//그려넣을 DC를 흰색으로 초기화


			//std::swap(m_CompleteHDC, m_DrawHDC);
			//Draw();
			//PatBlt(m_DrawHDC, -1, -1, (int)m_vecCurrentBufferSize.x + 1, (int)m_vecCurrentBufferSize.y + 1, WHITENESS);
		}

		void CRenderManager::RenderCall()
		{
			GET_SINGLE(SCENE).Render(m_DrawHDC);
			GET_SINGLE(OBJECT).Render(m_DrawHDC);

			GET_SINGLE(UI).Render(m_DrawHDC);

			GET_SINGLE(COLLISION).Render(m_DrawHDC);

			GET_SINGLE(TIME).Render(m_DrawHDC);
			GET_SINGLE(INPUT).Render(m_DrawHDC, 300, 300);
		}

		//void CRenderManager::Draw() const
		//{
		//	//완성된 DC를 출력
		//	BitBlt(
		//		m_hDC, //출력
		//		0, 0,  //Start
		//		(int)m_vecCurrentBufferSize.x, (int)m_vecCurrentBufferSize.y, //Size

		//		m_DrawHDC, //복사내용
		//		0, 0, //Start
		//		SRCCOPY);
		//}

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

		//void CRenderManager::ChangeScreenSize(bool maximumScale)
		//{
		//	m_bScreenState = maximumScale;

		//	if (maximumScale)
		//	{
		//		m_vecCurrentBufferSize = m_vecScreenSize;
		//	}
		//	else
		//	{
		//		m_vecCurrentBufferSize = m_vecWinSize;
		//	}

		//	RECT rect = { 0, 0, (LONG)m_vecCurrentBufferSize.x, (LONG)m_vecCurrentBufferSize.y };
		//	int xPos, yPos = 0;

		//	AdjustWindowRect(&rect, m_winStyle, false);

		//	if (maximumScale)
		//	{
		//		xPos = 0;
		//		yPos = 0;
		//	}
		//	else
		//	{
		//		xPos = ((int)(m_vecScreenSize.x - m_vecCurrentBufferSize.x) >> 1) - rect.left;
		//		yPos = ((int)(m_vecScreenSize.y - m_vecCurrentBufferSize.y) >> 1) - rect.top;
		//	}

		//	const int adjustedWidth = (rect.right - rect.left);
		//	const int adjustedHeight = (rect.bottom - rect.top);

		//	SetWindowPos(m_hWnd, nullptr,
		//		xPos, yPos,
		//		adjustedWidth, adjustedHeight,
		//		SWP_NOZORDER | SWP_NOACTIVATE);


		//	//새로운 사이즈의 비트맵 생성
		//	
		//}

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
			return m_pImageFactory;
		}
		ID2D1HwndRenderTarget* CRenderManager::GetRenderTarget()
		{
			return m_pRenderTarget;
		}

		void CRenderManager::SetCurBrush(const Color& color)
		{
			m_pCurBrush->SetColor(D2D1::ColorF(
				(FLOAT)color.r / 255.f,
				(FLOAT)color.g / 255.f,
				(FLOAT)color.b / 255.f,
				color.a));
		}

		void CRenderManager::SetCurFontSize(float fontSize)
		{
			if (m_pCurTextFormat->GetFontSize() != fontSize)
			{
				WCHAR fontFamilyName[255];
				WCHAR localName[255];

				m_pDefaultTextFormat->GetFontFamilyName(fontFamilyName, 255);
				m_pDefaultTextFormat->GetLocaleName(localName, 255);
				m_pCurTextFormat->Release();

				HRESULT hResult = m_pWriteFactory->CreateTextFormat(
					fontFamilyName,
					NULL,
					m_pDefaultTextFormat->GetFontWeight(),
					m_pDefaultTextFormat->GetFontStyle(),
					m_pDefaultTextFormat->GetFontStretch(),
					fontSize,
					localName,
					&m_pCurTextFormat
				);
			}
		}

		void CRenderManager::SetBrush(Color color)
		{
			m_pDefaultBrush->SetColor(
				D2D1::ColorF(
					(FLOAT)color.r / 255.f,
					(FLOAT)color.g / 255.f,
					(FLOAT)color.b / 255.f,
					color.a / 255.f)
			);
		}

		void CRenderManager::SetTextFormat(std::wstring fontName, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontstyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, std::wstring localName)
		{
			DWRITE_TEXT_ALIGNMENT textAlignment = m_pDefaultTextFormat->GetTextAlignment();
			DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment = m_pDefaultTextFormat->GetParagraphAlignment();

			if (m_pDefaultTextFormat != nullptr)
			{
				m_pDefaultTextFormat = nullptr;
				m_pDefaultTextFormat->Release();
			}
			HRESULT hResult = m_pWriteFactory->CreateTextFormat(
				fontName.c_str(),
				NULL,
				fontWeight,
				fontstyle,
				fontStretch,
				fontSize,
				localName.c_str(),
				&m_pDefaultTextFormat
			);
			assert(S_OK == hResult && L"TextFormat Create Failed");
		}

		void CRenderManager::SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlignment)
		{
			HRESULT hResult = m_pDefaultTextFormat->SetTextAlignment(textAlignment);
			assert(S_OK == hResult && L"TextFormat Set Alignment Failed");
		}

		void CRenderManager::SetTextParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment)
		{
			HRESULT hResult = m_pDefaultTextFormat->SetParagraphAlignment(paragraphAlignment);
			assert(S_OK == hResult && L"TextFormat SetParagraphAlignment Failed");
		}



		void CRenderManager::Text(const std::wstring& str, const Maths::Vector2& startPoint, const Maths::Vector2& endPoint)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			//const Maths::Vector2 end = pCam->CaluatePosition(endPoint);
			D2D1_RECT_F rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
			m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pDefaultTextFormat, rect, m_pDefaultBrush);
		}

		void CRenderManager::Text(const std::wstring& str, const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color, float fontSize)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			//const Maths::Vector2 end = pCam->CaluatePosition(endPoint);
			D2D1_RECT_F rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };

			SetCurFontSize(fontSize);
			SetCurBrush(color);
			m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pCurTextFormat, rect, m_pCurBrush);
		}

		void CRenderManager::Text(const std::wstring& str, float dstX, float dstY, float dstW, float dstH)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(Maths::Vector2(dstX, dstY));
			D2D1_RECT_F rect = { dstX, dstY,dstX + dstW, dstX + dstH };
			m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pDefaultTextFormat, rect, m_pDefaultBrush);
		}

		void CRenderManager::Text(const std::wstring& str, float dstX, float dstY, float dstW, float dstH, const Color& color, float fontSize)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(Maths::Vector2(dstX, dstY));
			D2D1_RECT_F rect = { dstX, dstY, dstX + dstW, dstX + dstH };

			SetCurFontSize(fontSize);
			SetCurBrush(color);
			m_pRenderTarget->DrawTextW(str.c_str(), (UINT32)str.size(), m_pCurTextFormat, rect, m_pCurBrush);
		}

		void CRenderManager::Line(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 vecStart = pCam->CaluatePosition(startPoint);
			//Maths::Vector2 vecEnd = pCam->CaluatePosition(startPoint);

			D2D1_POINT_2F start = { startPoint.x , startPoint.y };
			D2D1_POINT_2F end	= { endPoint.x , endPoint.y };
			m_pRenderTarget->DrawLine(start, end, m_pDefaultBrush);
		}

		void CRenderManager::Line(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color, float strokeWidth)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 vecStart = pCam->CaluatePosition(startPoint);
			//Maths::Vector2 vecEnd = pCam->CaluatePosition(startPoint);

			D2D1_POINT_2F start = { startPoint.x , startPoint.y };
			D2D1_POINT_2F end	= { endPoint.x , endPoint.y };
			SetCurBrush(color);
			m_pRenderTarget->DrawLine(start, end, m_pCurBrush);
		}

		void CRenderManager::FrameRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, float strokeWidth)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			//Maths::Vector2 end = pCam->CaluatePosition(endPoint);
			D2D1_RECT_F rect = { startPoint.x, startPoint.y, endPoint.x , endPoint.y };
			m_pRenderTarget->DrawRectangle(rect, m_pDefaultBrush, strokeWidth);
		}

		void CRenderManager::FrameRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color, float strokeWidth)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			//Maths::Vector2 end = pCam->CaluatePosition(endPoint);
			D2D1_RECT_F rect = { startPoint.x, startPoint.y, endPoint.x , endPoint.y };
			SetCurBrush(color);
			m_pRenderTarget->DrawRectangle(rect, m_pCurBrush, strokeWidth);
		}

		void CRenderManager::FillRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			//Maths::Vector2 end = pCam->CaluatePosition(endPoint);
			D2D1_RECT_F rect = { startPoint.x, startPoint.y, endPoint.x , endPoint.y };
			m_pRenderTarget->FillRectangle(rect, m_pDefaultBrush);
		}

		void CRenderManager::FillRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			//Maths::Vector2 end = pCam->CaluatePosition(endPoint);
			D2D1_RECT_F rect = { startPoint.x, startPoint.y, endPoint.x , endPoint.y };
			SetCurBrush(color);
			m_pRenderTarget->FillRectangle(rect, m_pCurBrush);
		}

		void CRenderManager::FrameEllipse(const Maths::Vector2& startPoint, float radius, float strokeWidth)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
			m_pRenderTarget->DrawEllipse(ellipse, m_pDefaultBrush, strokeWidth);
		}


		void CRenderManager::FrameEllipse(const Maths::Vector2& startPoint, float radius, const Color& color, float strokeWidth)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
			SetCurBrush(color);
			m_pRenderTarget->DrawEllipse(ellipse, m_pCurBrush, strokeWidth);
		}


		void CRenderManager::FillEllipse(const Maths::Vector2& startPoint, float radius)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
			m_pRenderTarget->FillEllipse(ellipse, m_pDefaultBrush);
		}


		void CRenderManager::FillEllipse(const Maths::Vector2& startPoint, float radius, const Color& color)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
			SetCurBrush(color);
			m_pRenderTarget->FillEllipse(ellipse, m_pCurBrush);
		}


		void CRenderManager::FrameCircle(const Maths::Vector2& startPoint, float radius)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
			m_pRenderTarget->DrawEllipse(ellipse, m_pDefaultBrush);
		}


		void CRenderManager::FrameCircle(const Maths::Vector2& startPoint, float radius, const Color& color, float strokeWidth)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y , radius , radius };
			SetCurBrush(color);
			m_pRenderTarget->DrawEllipse(ellipse, m_pCurBrush, strokeWidth);
		}


		void CRenderManager::FillCircle(const Maths::Vector2& startPoint, float radius)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
			m_pRenderTarget->FillEllipse(ellipse, m_pDefaultBrush);
		}

		void CRenderManager::FillCircle(const Maths::Vector2& startPoint, float radius, const Color& color)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			D2D1_ELLIPSE ellipse = { startPoint.x, startPoint.y ,radius , radius };
			SetCurBrush(color);
			m_pRenderTarget->FillEllipse(ellipse, m_pCurBrush);
		}

		void CRenderManager::Image(const Resource::CSprite* pImg, const Maths::Vector2& startPoint, float alpha)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(startPoint);
			const Maths::Vector2Int& scale = pImg->GetSize();
			const Maths::Vector2Int& leftTop = pImg->GetLeftTop();

			Maths::Vector2 start	= { startPoint.x - (scale.x * 0.5f)	, startPoint.y - scale.y };
			Maths::Vector2 end		= { startPoint.x + scale.x			, startPoint.y };

			D2D1_RECT_F srcImgRect = { (FLOAT)leftTop.x,	(FLOAT)leftTop.y,	(FLOAT)(leftTop.x + scale.x),	(FLOAT)(leftTop.y + scale.y) };

			//Maths::Vector2 end = pCam->CaluatePosition(Maths::Vector2(pos.));
			D2D1_RECT_F imgRect = { start.x, start.y, end.x, end.y };

			m_pRenderTarget->DrawBitmap(pImg->GetD2DImage(), imgRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcImgRect);
		}

		void CRenderManager::FrameImage(const Resource::CSprite* pImg, const Maths::Vector2& drawStartPoint, const Maths::Vector2& drawEndPoint, const Maths::Vector2& sliceStartPoint, const Maths::Vector2& sliceEndPoint, float alpha)
		{
			//CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			//Maths::Vector2 start = pCam->CaluatePosition(drawStartPoint);
			//Maths::Vector2 end = pCam->CaluatePosition(drawEndPoint);
			D2D1_RECT_F pointRect	= { drawStartPoint.x,	drawStartPoint.y,	drawEndPoint.x,		drawEndPoint.y };
			D2D1_RECT_F srcImgRect	= { sliceStartPoint.x,	sliceStartPoint.y,	sliceEndPoint.x,	sliceEndPoint.y };
			m_pRenderTarget->DrawBitmap(pImg->GetD2DImage(), pointRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcImgRect);
		}
}


}