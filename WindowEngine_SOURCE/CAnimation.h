#pragma once
#include "CResource.h"
#include "CTexture.h"

namespace Framework::Resource
{
    using namespace Maths;

    class CAnimator;
    class CTexture;

    class CAnimation :
        public CResource
    {
    public:
        struct Sprite
        {
            Maths::Vector2 leftTop; 
            Maths::Vector2 size;
            Maths::Vector2 offset;
            float  duration;
            Sprite():
                leftTop(Maths::Vector2::Zero),
                size(Maths::Vector2::Zero),
                offset(Maths::Vector2::Zero),
                duration(0.0f)
            {

            }
        };

        CAnimation();
        virtual ~CAnimation();

        HRESULT Load(const std::wstring& wstrPath) override;

        void Reset();
        void Tick();
        void Render(HDC hdc);

        void CreateAnimation(const std::wstring& name, Resource::CTexture* spriteSheet,
            Vector2 leftTop, Vector2 size, Vector2 offset,
            UINT spriteLength, float duration);

        bool IsCompleted() const { return m_bCompleted; }
        void SetOwner(CAnimator* pAnimator) { m_pOwner = pAnimator; }

    private:
        CAnimator* m_pOwner;
        CTexture* m_pTexture;

        std::vector<Sprite> m_vecSprites;
        int m_iIndex;
        float m_fTime;
        bool m_bLoop;
        bool m_bCompleted;
    };

}