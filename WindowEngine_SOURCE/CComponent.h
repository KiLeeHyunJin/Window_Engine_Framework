#pragma once
#include "CEntity.h"
namespace Framework
{
    class CGameObject;

    class CComponent :
        public CEntity
    {
    public :
        CGameObject* GetOwner()       const { return m_pOwner; }
        Enums::eComponentType GetComponentType() const { return m_eComponentType; }

        friend CGameObject;
    protected:
        CComponent(Enums::eComponentType eComopnentType);
        virtual ~CComponent();

    private:
        virtual void Initialize() = 0;
        virtual void Release() = 0;

        virtual void Tick() = 0;
        virtual void LastTick() = 0;

        virtual void Render(HDC hdc) = 0;

        void SetOwner(CGameObject* pOwner) { m_pOwner = pOwner; }

        Enums::eComponentType m_eComponentType;
        CGameObject* m_pOwner;
    };
}



