#include "CGameControllActor.h"
#include "ContentEnums.h"
#include "CEventManager.h"
#include "CObjectManager.h"

namespace Framework
{

    CGameControllActor::CGameControllActor(UINT layer) : CActor((UINT)eLayer::None)
    {
        UNREFERENCED_PARAMETER(layer);

        static bool create = false;
        if (create == false)
        {
            create = !create;
            return;
        }
        assert(false);
        //GET_SINGLE(EVENT).DeleteActor(this);
    }

    CGameControllActor::~CGameControllActor()
    {
    }

    CActor* CGameControllActor::GetPlayer() const
    {
        CActor* pGetPlayer = GET_SINGLE(OBJECT).GetActor(m_uiPlayerID);
        return pGetPlayer;
    }
    void CGameControllActor::Initialize()
    {
    }
    void CGameControllActor::BeginPlay()
    {
    }

    void CGameControllActor::Release()
    {
    }

    bool CGameControllActor::Tick()
    {
        return true;
    }

    bool CGameControllActor::LastTick()
    {
        return true;
    }

    void CGameControllActor::FixedTick()
    {
    }

    void CGameControllActor::Render(HDC hdc) const
    {
    }

}
