#pragma once
#include "CResource.h"

#include "CTexture.h"

namespace Framework
{
    namespace Resource
    {


        class CSprite : public CResource
        {
        public:
            CSprite(CTexture* m_pTexture, const Maths::Vector2Int& start, const Maths::Vector2Int& size, const Maths::Vector2Int& pivot);
            virtual ~CSprite();

            HRESULT Load(const std::wstring& wstrPath) override;

            const Maths::Vector2Int&    GetLeftTop()        const   { return m_vecStart;        }
            const Maths::Vector2Int&    GetSize()           const   { return m_vecSize;         }
            const Maths::Vector2Int&    GetPivot()          const   { return m_vecPivot;        }
            //int                         GetTransparent()    const   { return m_iTransparent;    }
            //void                SetTransparent(int transparent)     { m_iTransparent = transparent; }

            HDC                         GetHDC()            const   { return m_pTexture->GetHDC(); }
            //CTexture::eTextureType      GetTextureType()    const   { return m_pTexture->GetTextureType(); }
            //bool                        GetAlpha()          const   { return m_pTexture->GetAlpha(); }
            //Gdiplus::Image*             GetImage()          const   { return m_pTexture->GetImage(); }
            ID2D1Bitmap*                GetD2DImage()       const    { return m_pBitmap;  }
            void Render(HDC hdc) const;

        protected:


            //friend Manager::CResourceManager;
        private:
            Maths::Vector2Int m_vecStart;
            Maths::Vector2Int m_vecPivot;
            Maths::Vector2Int m_vecSize;
            //int m_iTransparent;
            HDC m_hdc = 0;
            CTexture* m_pTexture;

            ID2D1Bitmap* m_pBitmap;

            // CResource을(를) 통해 상속됨

        };

    }
}

