#pragma once
#include "CComponent.h"

namespace Framework
{
    class CTransformComponent :
        public CComponent
    {
    public :
        __forceinline float GetX() const            { return m_vecPos.x; }
        __forceinline float GetY() const            { return m_vecPos.y; }

        __forceinline float GetRot()                const { return m_fRot; }
        __forceinline const Maths::Vector2& GetPos()       const { return m_vecPos; }
        __forceinline const Maths::Vector2& GetScale()     const { return m_vecScale; }

        inline void SetRot(float rot)              { m_fRot = rot; }
        inline void SetPos(const Maths::Vector2& pos)     { m_vecPos = pos; }
        inline void SetScale(const Maths::Vector2& pos)   { m_vecScale = pos; }

        static constexpr Enums::eComponentType StaticComponentType()    {   return Enums::eComponentType::Transform;    }
        Enums::eComponentType GetComponentType() const override         {   return StaticComponentType();   }

        friend CGameObject;
    private:
        CTransformComponent();
        virtual ~CTransformComponent();
        // CComponent을(를) 통해 상속됨
        void Initialize() override;
        void Release() override;

        bool Tick() override;
        bool LastTick() override;

        void Render(HDC hdc) override;

        Maths::Vector2 m_vecPos;
        Maths::Vector2 m_vecScale;
        float m_fRot;

    };
}
