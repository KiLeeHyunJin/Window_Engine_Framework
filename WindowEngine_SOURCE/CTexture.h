#pragma once
#include "CResource.h"
namespace Framework
{
	class CTexture :
		public CResource
	{
	public:
		enum class eTextureType
		{
			Bmp,
			Png,
			None,
		};
		CTexture();
		virtual ~CTexture();
		HRESULT Load(const std::wstring& wstrPath) override;
		UINT	GetWidth() { return m_uiWidth; }
		UINT	GetHeight() { return m_uiWidth; }
		HDC		GetHDC() { return m_hdc; }
		eTextureType	GetTextureType() { return m_eTextureType; }
		Gdiplus::Image* GetImage() { return m_pImg; }
	private:

		Gdiplus::Image* m_pImg;
		HBITMAP m_hBmp;
		HDC m_hdc;

		UINT m_uiWidth;
		UINT m_uiHeight;
		eTextureType m_eTextureType;
		// CResource을(를) 통해 상속됨
	};

}

