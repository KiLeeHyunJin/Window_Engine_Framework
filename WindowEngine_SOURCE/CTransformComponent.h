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

        Maths::Vector2 GetPos() const          { return m_vecPos; }
        void SetPos(Maths::Vector2 pos)        { m_vecPos = pos; }

        friend CGameObject;
    private:
        CTransformComponent();
        virtual ~CTransformComponent();
        // CComponent��(��) ���� ��ӵ�
        void Initialize() override;

        void Release() override;

        void Tick() override;

        void LastTick() override;

        void Render(HDC hdc) override;

        Maths::Vector2 m_vecPos;

    };
}
