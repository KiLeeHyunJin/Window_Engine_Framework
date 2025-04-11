#pragma once
#include "CColliderComponent.h"



namespace Framework
{
	class CActor;
	class CCircleColliderComponent :
		public CColliderComponent
	{
	public:
		CCircleColliderComponent();
		virtual ~CCircleColliderComponent();

		// CComponent을(를) 통해 상속됨
		virtual void BeginPlay() override;
		virtual void Release() override;
		virtual bool TickComponent() override;
		virtual bool LastTickComponent() override;
		virtual void Render(HDC hdc) override;
		bool CheckCollision(CColliderComponent* other) override;

		//friend CActor;
	private:


		float m_fRadius;

		// CColliderComponent을(를) 통해 상속됨
	};
}



