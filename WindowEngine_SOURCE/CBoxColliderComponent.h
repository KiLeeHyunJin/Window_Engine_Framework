#pragma once
#include "CColliderComponent.h"

namespace Framework
{
	class CActor;
	class CBoxColliderComponent :
		public CColliderComponent
	{
	public:

		friend CActor;
	private:
		CBoxColliderComponent();
		virtual ~CBoxColliderComponent();

		// CComponent��(��) ���� ��ӵ�
		virtual void BeginPlay() override;
		virtual void Release() override;
		virtual bool TickComponent() override;
		virtual bool LastTickComponent() override;
		virtual void Render(HDC hdc) override;

		//Maths::Vector2 m_vecSize;


		// CColliderComponent��(��) ���� ��ӵ�
		bool CheckCollision(CColliderComponent* other) override;

	};


}

