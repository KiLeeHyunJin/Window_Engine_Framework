#include "CTexture.h"
#include "CApplication.h"
#include "CResourceManager.h"

extern Framework::CApplication application;

namespace Framework//::Resource
{
	namespace Resource
	{
		CTexture* CTexture::Create(std::wstring name, UINT width, UINT height, UINT count)
		{
			CTexture* pTexture = CResourceManager::Find<CTexture>(name);
			if (pTexture != nullptr)
			{
				return pTexture;
			}
			pTexture = new CTexture();
			pTexture->SetName(name);
			pTexture->SetHeight(height);
			pTexture->SetWidth(width);
			
			const HDC hdc = application.GetHDC();
			//HWND hwnd = application.GetHWND();

			pTexture->m_hBmp = CreateCompatibleBitmap(hdc, width, height);
			pTexture->m_hdc = CreateCompatibleDC(hdc);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(pTexture->m_hdc, pTexture->m_hBmp);

			///24bit¶ó ¹» ÇØµµ Èò»öÀÓ
			//HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

			//Rectangle(pTexture->m_hdc, -1, -1, pTexture->GetWidth(), pTexture->GetHeight());

			//transparentBrush = (HBRUSH)SelectObject(pTexture->m_hdc, oldBrush);
			DeleteObject(oldBitmap);

			CResourceManager::Insert(name, pTexture);
			return pTexture;
		}

		CTexture::CTexture() :
			CResource(Enums::eResourceType::Texture),
			m_uiHeight(0), m_uiWidth(0),
			m_hBmp(0), m_hdc(0), m_eTextureType(CTexture::eTextureType::Bmp), m_uiCount(1),
			m_pImg(nullptr), m_bAlpha(false)
		{	}


		CTexture::~CTexture()
		{	}

		HRESULT CTexture::Load(const std::wstring& wstrPath)
		{
			std::wstring ext = wstrPath.substr(wstrPath.find_last_of(L".") + 1);

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
			DeleteObject(oldBmp);

			return S_OK;
		}

	}

}