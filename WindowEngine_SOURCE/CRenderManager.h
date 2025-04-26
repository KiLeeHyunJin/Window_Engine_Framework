#pragma once
#include "CommonInclude.h"

namespace Framework
{

	namespace Resource
	{
		class CSprite;
	}

	class CApplication;
	

	namespace Manager
	{
		class CRenderManager 
		{
			DECLARE_SINGLE(CRenderManager)
			RELEASE_SINGLE(CRenderManager)
		public:

			__forceinline const Maths::Vector2Int& GetResolution() { return m_vecCurrentBufferSize; }

			friend CApplication;
		private:
			~CRenderManager();
			void Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen);
			void Release();

			void Render();

			void Draw() const;

			void AdjustWindow(HWND hWnd, int width, int height, int xPos, int yPos, DWORD winStyle, bool menu);
			void ChangeScreenSize(bool maximumScale);

			void CreateBackBuffer(int width, int height) const;

			HDC GetHDC() const  { return m_hDC; }

			HWND m_hWnd									= {};
			HDC m_hDC									= {};	//원본 DC

			HDC m_DrawHDC								= {};	//그리는 DC
			HDC m_CompleteHDC							= {};	//완성된 DC



			ID2D1Factory* m_pFactory					= nullptr;					//d2d팩토리
			ID2D1HwndRenderTarget* m_pRenderTarget		= nullptr;		//그려야하는 화면
			IWICImagingFactory* m_pImageFactory			= nullptr;		//이미지
			IDWriteFactory* m_pWriteFactory				= nullptr;			//그리기

			ID2D1SolidColorBrush* m_pDefaultBrush		= nullptr;		//도형 그리기 위한 브러시
			IDWriteTextFormat* m_pDefaultTextFormat		= nullptr;	//텍스트  그리기 위한

			ID2D1SolidColorBrush* m_pCurBrush			= nullptr;			//현재 브러시
			IDWriteTextFormat* m_pCurTextFormat			= nullptr;		//현재 포맷

		public:
			void SetBrush(Color color);
			void SetTextFormat(
				std::wstring fontName,
				DWRITE_FONT_WEIGHT fontWeight,
				DWRITE_FONT_STYLE fontstyle,
				DWRITE_FONT_STRETCH fontStretch,
				FLOAT fontSize,
				std::wstring localName = L"ko");

			void SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlignment);
			void SetTextParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);

			void Text(const std::wstring& str, const Maths::Vector2& startPoint, const Maths::Vector2& endPoint);
			void Text(const std::wstring& str, const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color, float fontSize);

			void Text(const std::wstring& str, float dstX, float dstY, float dstW, float dstH);
			void Text(const std::wstring& str, float dstX, float dstY, float dstW, float dstH, const Color& color, float fontSize);

			void Line(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint);
			void Line(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color, float strokeWidth = 1.f);

			void FrameRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, float strokeWidth = 1.f);
			void FrameRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color, float strokeWidth = 1.f);

			void FillRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint);
			void FillRect(const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, const Color& color);

			void FrameEllipse(const Maths::Vector2& startPoint, float radius, float strokeWidth = 1.f);
			void FrameEllipse(const Maths::Vector2& startPoint, float radius, const Color& color, float strokeWidth = 1.f);

			void FillEllipse(const Maths::Vector2& startPoint, float radius);
			void FillEllipse(const Maths::Vector2& startPoint, float radius, const Color& color);

			void FrameCircle(const Maths::Vector2& startPoint, float radius);
			void FrameCircle(const Maths::Vector2& startPoint, float radius, const Color& color, float strokeWidth = 1.f);

			void FillCircle(const Maths::Vector2& startPoint, float radius);
			void FillCircle(const Maths::Vector2& startPoint, float radius, const Color& color);

			void Image(Resource::CSprite* pImg, const Maths::Vector2& startPoint, const Maths::Vector2& endPoint, float alpha = 1.f);
			void FrameImage(Resource::CSprite* pImg,
				const Maths::Vector2& drawStartPoint, const Maths::Vector2& drawEndPoint,
				const Maths::Vector2& sliceStartPoint, const Maths::Vector2& sliceEndPoint, float alpha = 1.f);

			IWICImagingFactory* GetImageFactory();
			ID2D1HwndRenderTarget* GetRenderTarget();

		private:

			//HBITMAP m_BmpBuffer							= {};

			Maths::Vector2Int m_vecWinSize				= {};
			Maths::Vector2Int m_vecScreenSize			= {};
			Maths::Vector2Int m_vecCurrentBufferSize = {};

			DWORD m_winStyle							= 0;
			bool m_bScreenState							= false;

		};
	}

	
	using RENDER = Manager::CRenderManager;
//#define RENDER CRenderManager

}

