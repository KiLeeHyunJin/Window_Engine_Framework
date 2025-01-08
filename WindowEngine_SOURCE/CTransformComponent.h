#pragma once
#include "CComponent.h"

namespace Framework
{
    class CTransformComponent :
        public CComponent
    {
    public :
        CTransformComponent();
        virtual ~CTransformComponent();

        float GetX() const              { return m_vecPos.x; }
        float GetY() const              { return m_vecPos.y; }

        Maths::Vector2 GetPos() const          { return m_vecPos; }
        void SetPos(Maths::Vector2 pos)        { m_vecPos = pos; }

        // CComponent을(를) 통해 상속됨
        void Initialize() override;

        void Release() override;

        void Tick() override;

        void LastTick() override;

        void Render(HDC hdc) override;

    private:
        Maths::Vector2 m_vecPos;

    };
}
