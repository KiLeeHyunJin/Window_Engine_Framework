#pragma once
#include "CResource.h"
#include "CommonInclude.h"

namespace Framework//::Resource
{

	namespace Resource
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
			//static const CTexture* Create(const std::wstring& name, UINT width, UINT height, std::vector<Maths::Vector2>& sizes);

			HRESULT						Load(const std::wstring& wstrPath) override;
			inline UINT					GetWidth()	const			{ return m_uiWidth; }
			inline UINT					GetHeight()	const			{ return m_uiWidth; }

			//inline bool					GetAlpha()	const			{ return m_bAlpha; }
			//inline const eTextureType	GetTextureType() const		{ return m_eTextureType; }
			//inline Gdiplus::Image*		GetImage()	const		{ return m_pImg; }
			inline HDC					GetHDC()	const			{ return m_hdc; }
			ID2D1Bitmap*				GetBitmap() const			{ return m_pBitmap; }
			//inline void SetWidth(UINT width) { m_uiWidth = width; }
			//inline void SetHeight(UINT height) { m_uiHeight = height; }

			//friend Manager::CResourceManager;
		private:




			HDC m_hdc;

			HBITMAP m_hBmp;
			//Gdiplus::Image* m_pImg;

			UINT m_uiWidth;
			UINT m_uiHeight;

			//eTextureType m_eTextureType;

			ID2D1Bitmap* m_pBitmap = nullptr;
			bool m_bAlpha;
		};

	}
	
}

