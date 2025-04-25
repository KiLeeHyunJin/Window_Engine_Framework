#pragma once
#include "CActor.h"

namespace Framework
{

    class CGameControllActor :
        public CActor
    {
    public:
        CGameControllActor(UINT layer);
        virtual ~CGameControllActor();

        // CActor을(를) 통해 상속됨
        void BeginPlay() override;

        void Release() override;

        bool Tick() override;

        bool LastTick() override;

        void FixedTick() override;

        void Render(HDC hdc) const override;


        void        SetPlayerID(UINT32 uiPlayerID)      {    m_uiPlayerID = uiPlayerID;    }
        CActor*     GetPlayer() const;

    private:
        UINT32 m_uiPlayerID = 0;






        // CActor을(를) 통해 상속됨
        void Initialize() override;

    };
}


