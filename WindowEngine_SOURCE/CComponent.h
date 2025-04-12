#pragma once
#include "CEntity.h"

namespace Framework
{
    class CActor;

    class CComponent :
        public CEntity
    {
    public :
        __forceinline CActor* GetOwner()   const    { return m_pOwner; }
        //__forceinline Enums::eComponentType GetComponentType() const { return m_eComponentType; }
        virtual const Enums::eComponentType GetComponentType() const = 0;

        friend CActor;
    protected:
        CComponent(Enums::eComponentType eComopnentType);
        virtual ~CComponent();

    private:
        virtual void BeginPlay() = 0;
        virtual void Release() = 0;

        virtual bool TickComponent() = 0;
        virtual bool LastTickComponent() = 0;

        virtual void Render(HDC hdc) = 0;

        __inline void SetOwner(CActor* pOwner) { m_pOwner = pOwner; }

        Enums::eComponentType m_eComponentType;
        CActor* m_pOwner;
    };
}



