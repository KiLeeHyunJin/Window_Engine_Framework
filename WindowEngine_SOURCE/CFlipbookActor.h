#pragma once
#include "CActor.h"
#include "CommonInclude.h"

namespace Framework
{
    namespace Resource
    {
        class CFlipbook;
    }
    using namespace Resource;

    class CFlipbookActor :
        public CActor
    {
        DECLARE_PARENT(CActor)
    public:
        CFlipbookActor(UINT layer);
        virtual ~CFlipbookActor();

        void SetFlipbook(const CFlipbook* flipbook) 
        {  
            CFlipbook* pFlipbook = const_cast<CFlipbook*>(flipbook);
            m_pFlipbook = pFlipbook;
        }
        void Reset();

    protected:
        // CActor을(를) 통해 상속됨
        void BeginPlay() override;
        void Release() override;

        bool Tick() override;
        bool LastTick() override; 

        bool Render(HDC hdc) const override;

    private:
        void AnimationTickComponent();

        Resource::CFlipbook* m_pFlipbook;
        float m_fSumTime;
        INT m_uiIndex;
        bool m_bCompleted;

        // CActor을(를) 통해 상속됨
        void Initialize() override;
        void FixedTick() override;
    };


}
