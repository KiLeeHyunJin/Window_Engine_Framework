#include "CSprite.h"

#include "CTexture.h"
namespace Framework
{
    namespace Resource
    {

        CSprite::CSprite(CTexture* m_pTexture,const Maths::Vector2Int& start,const Maths::Vector2Int& size,const Maths::Vector2Int& pivot) :
            CResource(Enums::eResourceType::Sprite), m_pTexture(m_pTexture), m_vecStart(start), m_vecSize(size),
            m_vecPivot(pivot)
        {   }

        CSprite::~CSprite()
        {   }

        HRESULT CSprite::Load(const std::wstring & wstrPath)
        {
            return S_OK;
        }

        void CSprite::Render(HDC hdc) const
        {
        }
    }
}