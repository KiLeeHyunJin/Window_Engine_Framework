#pragma once
#include "CResource.h"
#include "CTexture.h"


namespace Framework
{
    using namespace Maths;
    using namespace Resource;

    class CAnimatorComponent;

    class CAnimation :
        public CResource
    {
    public:
        struct Sprite
        {
            Maths::Vector2 leftTop; 
            //Maths::Vector2 size;
            //Maths::Vector2 offset;
            //float  duration;
            Sprite():
                leftTop(Maths::Vector2::Zero)//,
                //size(Maths::Vector2::Zero),
                //offset(Maths::Vector2::Zero),
                //duration(0.0f)
            {

            }
        };

        CAnimation();
        virtual ~CAnimation();

        HRESULT Load(const std::wstring& wstrPath) override;

        void Reset();
        void Tick();
        void Render(HDC hdc);

        void CreateAnimation(const std::wstring& name, CTexture* spriteSheet,
            const Vector2& leftTop, /*Vector2 size, Vector2 offset,*/
            UINT spriteLength, float duration);

        inline bool IsCompleted() const { return m_bCompleted; }
        void SetOwner(CAnimatorComponent* pAnimator) { m_pOwner = pAnimator; }

    private:
        void RenderBMP(HDC hdc, float rot,const Maths::Vector2& pos,const Maths::Vector2& scale,const Sprite& sprite) const;
        void RenderPNG(HDC hdc, float rot,const Maths::Vector2& pos,const Maths::Vector2& scale,const Sprite& sprite) const;

        void (CAnimation::* RenderFunc[(int)Resource::CTexture::eTextureType::None])
            (HDC hdc, float rot,const Maths::Vector2& pos,const Maths::Vector2& scale, const Sprite& sprite)  const;

        CAnimatorComponent* m_pOwner;
        CTexture* m_pTexture;
        std::vector<Sprite> m_vecSprites;
        
        //bool m_bLoop;
        bool m_bCompleted;

        INT m_iIndex;
        float m_fTime;
        float m_fDuration;
    };

}