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

		// CComponent을(를) 통해 상속됨
		virtual void Initialize() override;
		virtual void Release() override;
		virtual void Tick() override;
		virtual void LastTick() override;
		virtual void Render(HDC hdc) override;

		float m_fRadius;
	};
}



