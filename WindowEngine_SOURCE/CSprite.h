#pragma once
#include "CResource.h"
#include "Maths.h"
namespace Framework
{
    namespace Resource
    {
        class CTexture;

        class CSprite : public CResource
        {
        public:


            const Maths::Vector2Int&    GetSize() const         { return m_vecSize;         }
            const Maths::Vector2Int&    GetPivot() const        { return m_vecPivot;        }
            int                         GetTransparent() const  { return m_iTransparent;    }
            HDC                         GetHDC() const;
            void Render(HDC hdc) const;
        protected:
            CSprite(CTexture* m_pTexture,const Maths::Vector2Int& start, const Maths::Vector2Int& size,const Maths::Vector2Int& pivot = Maths::Vector2Int::Zero);
            virtual ~CSprite();

        private:
            Maths::Vector2Int m_vecStart;
            Maths::Vector2Int m_vecEnd;
            Maths::Vector2Int m_vecPivot;
            Maths::Vector2Int m_vecSize;
            int m_iTransparent;
            //HDC m_hdc;
            CTexture* m_pTexture;

        };

    }
}

