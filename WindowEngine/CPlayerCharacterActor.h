#pragma once
#include "..//WindowEngine_SOURCE//CFlipbookActor.h"

namespace Framework
{

    class CPlayerCharacterActor :
        public CFlipbookActor
    {
        DECLARE_PARENT(CFlipbookActor)
    public : 
        CPlayerCharacterActor(UINT layer);
        virtual ~CPlayerCharacterActor();

        void Initialize() override;

        void BeginPlay() override;

        void Release() override;

        bool Tick() override;
        bool LastTick() override;

        bool Render(HDC hdc) const override;
        void FixedTick() override;
        void SetTileCollision() { m_iTileCollisionCount++; }

    private:
        INT m_iTileCollisionCount = 0;


    };
}


