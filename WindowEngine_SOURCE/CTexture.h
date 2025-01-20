#pragma once
#include "CResource.h"
namespace Framework::Resource
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

		static CTexture* Create(std::wstring name, UINT width, UINT height);

		CTexture();
		virtual ~CTexture();
		HRESULT Load(const std::wstring& wstrPath) override;
		UINT	GetWidth()					{ return m_uiWidth;		}
		UINT	GetHeight()					{ return m_uiWidth;		}
		bool	GetAlpha()					{ return m_bAlpha;		}

		HDC		GetHDC()					{ return m_hdc;			}
		eTextureType	GetTextureType()	{ return m_eTextureType; }
		Gdiplus::Image* GetImage()			{ return m_pImg;		}

	private:
		void SetWidth(UINT width)	{ m_uiWidth = width; }
		void SetHeight(UINT height) { m_uiHeight = height; }
		Gdiplus::Image* m_pImg;
		HBITMAP m_hBmp;
		HDC m_hdc;

		UINT m_uiWidth;
		UINT m_uiHeight;
		eTextureType m_eTextureType;

		bool m_bAlpha;
		// CResource을(를) 통해 상속됨
	};

}

