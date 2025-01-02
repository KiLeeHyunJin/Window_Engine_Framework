#pragma once
#include "CComponent.h"

namespace Framework
{
    class CTransform :
        public CComponent
    {
    public :
        CTransform();
        virtual ~CTransform();

        float GetX() const              { return m_fX; }
        float GetY() const              { return m_fY; }
        void SetPos(float x, float y)   { m_fX = x; 
                                          m_fY = y; }

        // CComponent을(를) 통해 상속됨
        void Initialize() override;

        void Release() override;

        void Tick() override;

        void LastTick() override;

        void Render(HDC hdc) override;

    private:
        float m_fX;
        float m_fY;

    };
}
