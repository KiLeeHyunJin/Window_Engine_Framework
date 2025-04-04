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

		// CComponent을(를) 통해 상속됨
		virtual void BeginPlay() override;
		virtual void Release() override;
		virtual bool Tick() override;
		virtual bool LastTick() override;
		virtual void Render(HDC hdc) override;

		//Maths::Vector2 m_vecSize;

	};


}

