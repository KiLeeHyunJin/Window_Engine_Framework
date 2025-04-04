#include "CSprite.h"
#include "Enums.h"
#include "CTexture.h"
namespace Framework
{
    namespace Resource
    {

        CSprite::CSprite(CTexture* m_pTexture,const Maths::Vector2Int& start,const Maths::Vector2Int& size,const Maths::Vector2Int& pivot) :
            CResource(Enums::eResourceType::Sprite), m_pTexture(m_pTexture), m_vecStart(start), m_vecSize(m_vecSize), m_vecPivot(pivot)
        {
            m_vecEnd = m_vecStart + m_vecSize;
        }
        CSprite::~CSprite()
        {
        }

        HDC CSprite::GetHDC() const         {    return m_pTexture->GetHDC();    }

        void CSprite::Render(HDC hdc) const
        {
        }
    }
}