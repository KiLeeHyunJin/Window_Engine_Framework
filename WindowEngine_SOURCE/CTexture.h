#pragma once
#include "CResource.h"
namespace Framework::Resource
{
	class CResourceManager;

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



		HRESULT Load(const std::wstring& wstrPath) override;
		inline UINT	GetWidth()	const { return m_uiWidth;		}
		inline UINT	GetHeight()	const { return m_uiWidth;		}
		inline bool	GetAlpha()	const { return m_bAlpha;		}

		inline HDC	GetHDC()	const { return m_hdc;			}
		inline const eTextureType	GetTextureType() const	{ return m_eTextureType; }
		inline Gdiplus::Image* GetImage()	const		{ return m_pImg;		}


		friend CResourceManager;
	private:
		CTexture();
		virtual ~CTexture();

		inline void SetWidth(UINT width)	{ m_uiWidth = width; }
		inline void SetHeight(UINT height) { m_uiHeight = height; }

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

