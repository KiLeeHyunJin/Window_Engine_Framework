#pragma once
#include "CEntity.h"
namespace Framework
{
    class CGameObject;

    class CComponent :
        public CEntity
    {
    public :

        virtual void Initialize()       = 0;
        virtual void Release()          = 0;

        virtual void Tick()             = 0;
        virtual void LastTick()         = 0;

        virtual void Render(HDC hdc)    = 0;

        void SetOwner(CGameObject* pOwner)  { m_pOwner = pOwner; }
        CGameObject* GetOwner()             { return m_pOwner; }
        Enums::eComponentType GetComponentType() const { return m_eComponentType; }

    protected:
        Enums::eComponentType m_eComponentType;
        CComponent(Enums::eComponentType eComopnentType);
        virtual ~CComponent();

    private:
        CGameObject* m_pOwner;
    };
}



