#pragma once
#include "CColliderComponent.h"

namespace Framework
{
	class CActor;
	class CBoxColliderComponent :
		public CColliderComponent
	{
		DECLARE_PARENT(CColliderComponent)
	public:
		RECT GetRect();

		CBoxColliderComponent();
		virtual ~CBoxColliderComponent();

		// CComponent을(를) 통해 상속됨
		virtual void BeginPlay() override;
		virtual void Release() override;
		virtual bool TickComponent() override;
		virtual bool LastTickComponent() override;
		virtual void Render(HDC hdc) override;

		// CColliderComponent을(를) 통해 상속됨
		const bool CheckCollision(CColliderComponent* other) override;

		//friend CActor;
	private:


	};


}

