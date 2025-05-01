#pragma once
#include "CComponent.h"
#include "CTimeManager.h"
#include "CRenderer.h"
#include "CCameraComponent.h"

namespace Framework
{
	class CActor;
	class CColliderComponent;
	class CBoxColliderComponent;

	class CRigidbodyComponent :
		public CComponent
	{
	public:
		CRigidbodyComponent();
		virtual ~CRigidbodyComponent();
		// CComponent��(��) ���� ��ӵ�
		virtual void BeginPlay() override			{				}
		virtual void Release() override				{				}
		virtual bool TickComponent() override;
		virtual bool LastTickComponent() override	{ return true;	}
		virtual void Render(HDC hdc) override		{				}

		static constexpr Enums::eComponentType	StaticComponentType()				{ return Enums::eComponentType::Rigidbody; }
		const Enums::eComponentType				GetComponentType() const override	{ return StaticComponentType(); }

		float GetCurrentGravity()			const { return m_fGravityValue; }
		void SetCurrentGravity(float gravity)		{ m_fGravityValue = gravity; }
		void SetFriction(float friction)			{ m_fFriction = friction; }
		/// <summary>
		/// ������ ����
		/// </summary>
		void SetMass(float mass) { m_fMass = mass; }
		/// <summary>
		/// �������� ���� ����
		/// </summary>
		void SetForce(Maths::Vector2 force)			{ m_vecForce = force; }
		/// <summary>
		/// �߷��� �缳��
		/// </summary>
		///void SetGravity(Maths::Vector2 gravity)		{ m_vecGravity = gravity; }
		/// <summary>
		/// �ӷ��� �缳��
		/// </summary>
		void SetVelocity(Maths::Vector2 velocity)	{ m_vecVelocity = velocity;	}
		/// <summary>
		/// �������� ���� �߰�
		/// </summary>
		void SetAddForce(Maths::Vector2 addForce)	{ m_vecForce += addForce; }

		void AddVelocity(Maths::Vector2& addVelocity) { m_vecVelocity += addVelocity; }

		void SetGround(bool isGround);
		bool GetGround()				const		{ return m_bGround; }

		void SetFreeze(bool state)					{ m_bFreeze = state; }
		bool GetFreeze()				const		{ return m_bFreeze; }
		const Maths::Vector2& GetVelocity()	const		{ return m_vecVelocity; }
		const Maths::Vector2& GetForce()		const		{ return m_vecForce;}

		float GetMass() const						{ return m_fMass; }
		float GetFriction() const					{ return m_fFriction; }


		//�浹ü���� �о�ų� �ö�Ÿ�ų� �ϴ� ��������� ����
		static void		AdjustPosition(CBoxColliderComponent* target, CBoxColliderComponent* other);
	
		//friend CActor;
	private:

		static bool		CheckCollisionLine(CBoxColliderComponent* target, CBoxColliderComponent* other);
		//�ι��� �о��
		static void		DiagonalAdjustPosition(const Maths::Vector2& moveSqrDir, const RECT& collisionRect, CBoxColliderComponent* targetBoxCollider, CBoxColliderComponent* otherBoxCollider);
		//�ѹ��� �о��
		static void		SimpleAdjustPosition(const RECT& collisionRect, CBoxColliderComponent* targetBoxCollider, CBoxColliderComponent* otherBoxCollider);


		void VelocityCompute();
		void LimitSpeedCompute();
		void ChangePosition();

		/// <summary>
		/// ����
		/// </summary>
		float m_fMass;
		/// <summary>
		/// ������
		/// </summary>
		float m_fFriction;

		//�߷� ���� ��
		float m_fGravityValue = 0;
		/// <summary>
		/// �������� ��
		/// </summary>
		Maths::Vector2 m_vecForce;
		/// <summary>
		/// �ӵ�
		/// </summary>
		Maths::Vector2 m_vecVelocity;
		/// <summary>
		/// �߷�
		/// </summary>
		const Maths::Vector2 m_vecGravity;
		/// <summary>
		/// ���ӵ�
		/// </summary>
		Maths::Vector2 m_vecAccelation;

		Maths::Vector2 m_vecLimitVelocity;

		//Maths::Vector2 m_vecMoveValue;
		bool m_bFreeze = false;
		bool m_bGround;

		// CComponent��(��) ���� ��ӵ�
		void FixedComponent() override;
};

}



