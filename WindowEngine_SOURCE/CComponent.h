#pragma once
#include "CEntity.h"
namespace Framework
{
    class CGameObject;

    class CComponent :
        public CEntity
    {
    public :
        __forceinline CGameObject* GetOwner()   const    { return m_pOwner; }
        //__forceinline Enums::eComponentType GetComponentType() const { return m_eComponentType; }
        virtual Enums::eComponentType GetComponentType() const = 0;

        friend CGameObject;
    protected:
        CComponent(Enums::eComponentType eComopnentType);
        virtual ~CComponent();

    private:
        virtual void Initialize() = 0;
        virtual void Release() = 0;

        virtual bool Tick() = 0;
        virtual bool LastTick() = 0;

        virtual void Render(HDC hdc) = 0;

        __inline void SetOwner(CGameObject* pOwner) { m_pOwner = pOwner; }

        Enums::eComponentType m_eComponentType;
        CGameObject* m_pOwner;
    };
}



