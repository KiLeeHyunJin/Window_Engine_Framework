#pragma once
#include "CResource.h"
#include "CTexture.h"


namespace Framework
{
    namespace Resource
    {
        class CSprite;
    }
    using namespace Maths;
    using namespace Resource;

    class CAnimatorComponent;

    class CAnimation :
        public CResource
    {
    public:

        CAnimation();
        virtual ~CAnimation();

        void CreateAnimation(const std::wstring& name, bool loop = true);
        void AddSprite(CSprite* sprite, float duration = 1) { m_vecSprites.push_back(std::make_pair(sprite, duration)); }
        //void AddSprite(const Resource::CSprite* sprite, float duration);

        HRESULT Load(const std::wstring& wstrPath) override { return S_OK; }

        void Reset();
        void TickComponent();
        void Render(HDC hdc);

        inline bool IsCompleted() const { return m_bCompleted; }
        void SetOwner(CAnimatorComponent* pAnimator) { m_pOwner = pAnimator; }

    private:
        void RenderBMP(HDC hdc, float rot,const Maths::Vector2& pos,const Maths::Vector2& scale) const;
        //void RenderPNG(HDC hdc, float rot,const Maths::Vector2& pos,const Maths::Vector2& scale) const;

       /* void (CAnimation::* RenderFunc[(int)Resource::CTexture::eTextureType::None])
            (HDC hdc, float rot,const Maths::Vector2& pos,const Maths::Vector2& scale)  const;*/

        CAnimatorComponent* m_pOwner;
        std::vector<std::pair<Resource::CSprite*, float>> m_vecSprites;
        bool m_bLoop;
        bool m_bCompleted;
        INT m_iIndex;
        float m_fTime;
    };

}