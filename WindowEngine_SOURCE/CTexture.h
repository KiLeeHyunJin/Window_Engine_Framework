#pragma once
#include "CResource.h"
#include "CommonInclude.h"

namespace Framework//::Resource
{
	namespace Resource
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

			//static const CTexture* Create(const std::wstring& name, UINT width, UINT height, std::vector<Maths::Vector2>& sizes);

			HRESULT						Load(const std::wstring& wstrPath) override;
			inline UINT					GetWidth()	const			{ return m_uiWidth; }
			inline UINT					GetHeight()	const			{ return m_uiWidth; }

			inline bool					GetAlpha()	const			{ return m_bAlpha; }
			inline const eTextureType	GetTextureType() const		{ return m_eTextureType; }
			inline Gdiplus::Image*		GetImage()	const			{ return m_pImg; }
			inline HDC					GetHDC()	const			{ return m_hdc; }
			friend CResourceManager;
		private:
			CTexture();
			virtual ~CTexture();

			inline void SetWidth(UINT width) { m_uiWidth = width; }
			inline void SetHeight(UINT height) { m_uiHeight = height; }

			HDC m_hdc;

			HBITMAP m_hBmp;
			Gdiplus::Image* m_pImg;

			UINT m_uiWidth;
			UINT m_uiHeight;

			eTextureType m_eTextureType;
			bool m_bAlpha;
		};

	}
	
}

