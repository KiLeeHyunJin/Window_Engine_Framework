#include "CTexture.h"
#include "CApplication.h"
#include "CResourceManager.h"
#include "CRenderManager.h"

extern Framework::CApplication application;

namespace Framework//::Resource
{
	namespace Resource
	{
//		const CTexture* CTexture::Create(const std::wstring& name, UINT width, UINT height, std::vector<Maths::Vector2>& sizes)
//		{
//			const CTexture* pFindTexture = CResourceManager::FindTexture(name);
//			if (pFindTexture != nullptr)
//			{
//				return pFindTexture;
//			}
//			CTexture*  pTexture = new CTexture();
//			const UINT size = (UINT)sizes.size();
//			pTexture->SetCreateState();
//			pTexture->SetCount(size);
//			pTexture->SetName(name);
//			pTexture->SetHeight(height);
//			pTexture->SetWidth(width);
//			////?????????
//			//for(const auto& size : sizes)
//			//{
//			//	pTexture->PushBackSize(size);
//			//}
//
//			const HDC hdc		= application.GetHDC();
//			pTexture->m_hBmp	= ::CreateCompatibleBitmap(hdc, width, height);
//			pTexture->m_hdc		= ::CreateCompatibleDC(hdc);
//
//			HBITMAP oldBitmap = (HBITMAP)SelectObject(pTexture->m_hdc, pTexture->m_hBmp);
//
//#pragma region MyRegion
//			///24bit¶ó ¹» ÇØµµ Èò»öÀÓ
//			//HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
//			//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);
//			
//			//Rectangle(pTexture->m_hdc, -1, -1, pTexture->GetWidth(), pTexture->GetHeight());
//			
//			//transparentBrush = (HBRUSH)SelectObject(pTexture->m_hdc, oldBrush);
//#pragma endregion
//			DeleteObject(oldBitmap);
//
//			//CResourceManager::Insert(name, pTexture);
//			return pTexture;
//		}

		CTexture::CTexture() :
			CResource(Enums::eResourceType::Texture),
			m_uiHeight(0), m_uiWidth(0),
			m_hBmp(0), m_hdc(0), //m_eTextureType(CTexture::eTextureType::Bmp), m_pImg(nullptr),
			m_bAlpha(false), m_pBitmap(nullptr)
		{	}


		CTexture::~CTexture()
		{	}

		HRESULT CTexture::Load(const std::wstring& wstrPath)
		{
			/*std::wstring ext = wstrPath.substr(wstrPath.find_last_of(L".") + 1);

			if (ext == L"png")
			{
				m_eTextureType = eTextureType::Png;
				Gdiplus::Bitmap* pngImage = new Gdiplus::Bitmap(wstrPath.c_str());
				m_pImg = Gdiplus::Image::FromFile(wstrPath.c_str());
				if (m_pImg == nullptr)
				{
					return S_FALSE;
				}
				pngImage->GetHBITMAP(Gdiplus::Color::White, &m_hBmp);

				m_uiWidth = m_pImg->GetWidth();
				m_uiHeight = m_pImg->GetHeight();

			}
			else if (ext == L"bmp")
			{
				m_eTextureType = eTextureType::Bmp;
				m_hBmp = (HBITMAP)LoadImageW(nullptr, wstrPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				if (m_hBmp == nullptr)
				{
					return S_FALSE;
				}
				BITMAP info = {};
				GetObject(m_hBmp, sizeof(BITMAP), &info);
				m_uiHeight = info.bmHeight;
				m_uiWidth = info.bmWidth;
				m_bAlpha = info.bmBitsPixel == 32;
			}

			HDC mainDC = application.GetHDC();
			m_hdc = CreateCompatibleDC(mainDC);
			HBITMAP oldBmp = (HBITMAP)SelectObject(m_hdc, m_hBmp);
			DeleteObject(oldBmp);*/

			IWICBitmapDecoder* p_decoder;
			IWICBitmapFrameDecode* p_frame;
			IWICFormatConverter* p_converter;

			HRESULT hResult;
			hResult = GET_SINGLE(RENDER).GetImageFactory()->CreateDecoderFromFilename(wstrPath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder);
			assert(hResult == S_OK && L"DecoderFromFilename Faild");

			hResult = p_decoder->GetFrame(0, &p_frame);
			assert(hResult == S_OK && L"GetFrame Faild");

			hResult = GET_SINGLE(RENDER).GetImageFactory()->CreateFormatConverter(&p_converter);
			assert(hResult == S_OK && L"CreateFormatConverter Faild");

			hResult = p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);
			assert(hResult == S_OK && L"converter Initialize Faild");

			hResult = GET_SINGLE(RENDER).GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &m_pBitmap);
			assert(hResult == S_OK && L"CreateBitmap Faild");

			p_frame->GetSize(&m_uiWidth, &m_uiHeight);

			p_converter->Release();
			p_frame->Release();
			p_decoder->Release();
			return S_OK;
		}

	}

}