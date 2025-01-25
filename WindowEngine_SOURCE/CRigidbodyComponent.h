#pragma once
#include "CComponent.h"


namespace Framework
{
	class CGameObject;

	class CRigidbodyComponent :
		public CComponent
	{
	public:

		friend CGameObject;
	private:
		CRigidbodyComponent();
		virtual ~CRigidbodyComponent();
		// CComponent을(를) 통해 상속됨
		virtual void Initialize() override;
		virtual void Release() override;
		virtual void Tick() override;
		virtual void LastTick() override;
		virtual void Render(HDC hdc) override;

		/// <summary>
		/// 질량
		/// </summary>
		float m_fMass;
		/// <summary>
		/// 마찰력
		/// </summary>
		float m_fFriction;

		/// <summary>
		/// 가해지는 힘
		/// </summary>
		Maths::Vector2 m_vecForce;
		/// <summary>
		/// 속도
		/// </summary>
		Maths::Vector2 m_vecVelocity;
		/// <summary>
		/// 중력
		/// </summary>
		Maths::Vector2 m_vecGravity;
		/// <summary>
		/// 가속도
		/// </summary>
		Maths::Vector2 m_vecAccelation;

	};

}


