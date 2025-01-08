#include "CTexture.h"
#include "CApplication.h"

extern Framework::CApplication application;

namespace Framework::Resource
{
	CTexture::CTexture() :
		CResource(Enums::eResourceType::Texture),
		m_uiHeight(0), m_uiWidth(0),
		m_hBmp(0),m_hdc(0), m_pImg(nullptr)
	{
	}
	CTexture::~CTexture()
	{
	}
	HRESULT CTexture::Load(const std::wstring& wstrPath)
	{
		std::wstring ext = wstrPath.substr(wstrPath.find_last_of(L".") + 1);

		if (ext == L"png")
		{
			m_eTextureType = eTextureType::Png;
			m_pImg = Gdiplus::Image::FromFile(wstrPath.c_str());
			if (m_pImg == nullptr)
			{
				return S_FALSE;
			}

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
			m_uiHeight	= info.bmHeight;
			m_uiWidth	= info.bmWidth;

			HDC mainDC = application.GetHDC();
			m_hdc = CreateCompatibleDC(mainDC);
			HBITMAP oldBmp = (HBITMAP)SelectObject(m_hdc, m_hBmp);
			DeleteObject(oldBmp);
		}

		
		return S_OK;
	}
}