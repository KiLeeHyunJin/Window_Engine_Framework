#pragma once
#include "CComponent.h"

namespace Framework
{
    class CTransformComponent :
        public CComponent
    {
    public :
        float GetX() const              { return m_vecPos.x; }
        float GetY() const              { return m_vecPos.y; }

        float GetRot()              const { return m_fRot; }
        Maths::Vector2 GetPos()     const { return m_vecPos; }
        Maths::Vector2 GetScale()   const { return m_vecScale; }

        void SetRot(float rot)              { m_fRot = rot; }
        void SetPos(Maths::Vector2 pos)     { m_vecPos = pos; }
        void SetScale(Maths::Vector2 pos)   { m_vecScale = pos; }

        friend CGameObject;
    private:
        CTransformComponent();
        virtual ~CTransformComponent();
        // CComponent을(를) 통해 상속됨
        void Initialize() override;

        void Release() override;

        void Tick() override;

        void LastTick() override;

        void Render(HDC hdc) override;

        Maths::Vector2 m_vecPos;
        Maths::Vector2 m_vecScale;
        float m_fRot;

    };
}
