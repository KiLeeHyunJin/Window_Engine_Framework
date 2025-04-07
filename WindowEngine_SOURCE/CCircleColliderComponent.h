#pragma once
#include "CColliderComponent.h"



namespace Framework
{
	class CActor;
	class CCircleColliderComponent :
		public CColliderComponent
	{
	public:

		friend CActor;
	private:
		CCircleColliderComponent();
		virtual ~CCircleColliderComponent();

		// CComponent��(��) ���� ��ӵ�
		virtual void BeginPlay() override;
		virtual void Release() override;
		virtual bool TickComponent() override;
		virtual bool LastTickComponent() override;
		virtual void Render(HDC hdc) override;

		float m_fRadius;

		// CColliderComponent��(��) ���� ��ӵ�
		bool CheckCollision(CColliderComponent* other) override;
	};
}



