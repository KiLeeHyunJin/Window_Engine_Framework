#pragma once
#include "CColliderComponent.h"

namespace Framework
{
	class CActor;
	class CBoxColliderComponent :
		public CColliderComponent
	{
	public:
		RECT GetRect();

		CBoxColliderComponent();
		virtual ~CBoxColliderComponent();

		// CComponent��(��) ���� ��ӵ�
		virtual void BeginPlay() override;
		virtual void Release() override;
		virtual bool TickComponent() override;
		virtual bool LastTickComponent() override;
		virtual void Render(HDC hdc) override;

		// CColliderComponent��(��) ���� ��ӵ�
		bool CheckCollision(CColliderComponent* other) override;

		//friend CActor;
	private:


	};


}

