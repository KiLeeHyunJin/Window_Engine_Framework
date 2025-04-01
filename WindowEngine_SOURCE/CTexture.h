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

			static CTexture* Create(const std::wstring& name, UINT width, UINT height, std::vector<Maths::Vector2>& sizes);

			HRESULT		Load(const std::wstring& wstrPath) override;
			inline UINT	GetWidth()	const { return m_uiWidth; }
			inline UINT	GetHeight()	const { return m_uiWidth; }
			inline UINT GetCount() const { return m_uiCount; }

			inline bool	GetAlpha()	const { return m_bAlpha; }
			inline bool OnCreate() const { return m_bCreate; }

			inline const std::vector<Maths::Vector2>& GetSpriteSize() { return m_vecSizes; }
			inline const eTextureType	GetTextureType() const { return m_eTextureType; }
			inline Gdiplus::Image* GetImage()	const { return m_pImg; }
			inline HDC	GetHDC()	const { return m_hdc; }

			friend CResourceManager;
		private:
			CTexture();
			virtual ~CTexture();

			inline void SetWidth(UINT width) { m_uiWidth = width; }
			inline void SetHeight(UINT height) { m_uiHeight = height; }
			//void SetOffset(const Maths::Vector2& offset) { m_vecOffset = offset; }
			void PushBackSize(const Maths::Vector2& size) { m_vecSizes.push_back(size); }
			void SetCreateState() { m_bCreate = true; }
			void SetCount(UINT count) 
			{ 
				m_uiCount = count;  
				m_vecSizes.reserve(count); 
			}


			HBITMAP m_hBmp;
			HDC m_hdc;

			Gdiplus::Image* m_pImg;
			eTextureType m_eTextureType;

			UINT m_uiWidth;
			UINT m_uiHeight;
			UINT m_uiCount;

			bool m_bAlpha;
			bool m_bCreate;

			std::vector<Maths::Vector2> m_vecSizes;


			// CResource을(를) 통해 상속됨
		};

	}
	
}

