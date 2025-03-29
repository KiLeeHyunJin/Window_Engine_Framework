#pragma once
#include "CColliderComponent.h"



namespace Framework
{
	class CGameObject;
	class CCircleColliderComponent :
		public CColliderComponent
	{
	public:

		friend CGameObject;
	private:
		CCircleColliderComponent();
		virtual ~CCircleColliderComponent();

		// CComponent��(��) ���� ��ӵ�
		virtual void Initialize() override;
		virtual void Release() override;
		virtual bool Tick() override;
		virtual bool LastTick() override;
		virtual void Render(HDC hdc) override;

		float m_fRadius;
	};
}



