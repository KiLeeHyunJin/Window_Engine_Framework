#pragma once
#include "CComponent.h"
#include "CTimeManager.h"
#include "CRenderer.h"
#include "CCameraComponent.h"

namespace Framework
{
	class CActor;

	class CRigidbodyComponent :
		public CComponent
	{
	public:
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
		void SetGravity(Maths::Vector2 gravity)		{ m_vecGravity = gravity; }
		/// <summary>
		/// �ӷ��� �缳��
		/// </summary>
		void SetVelocity(Maths::Vector2 velocity)	{ m_vecVelocity = velocity;	}
		/// <summary>
		/// �������� ���� �߰�
		/// </summary>
		void SetAddForce(Maths::Vector2 addForce)	{ m_vecForce += addForce; }

		void SetGround(bool isGround) { m_bGround = isGround; }

		Maths::Vector2 GetVelocity() const			{ return m_vecVelocity; }
		Maths::Vector2 GetForce() const				{ return m_vecForce;}

		float GetMass() const						{ return m_fMass; }
		float GetFriction() const					{ return m_fFriction; }

		static constexpr Enums::eComponentType StaticComponentType() { return Enums::eComponentType::Rigidbody; }
		const Enums::eComponentType GetComponentType() const override { return StaticComponentType(); }

		friend CActor;
	private:
		CRigidbodyComponent();
		virtual ~CRigidbodyComponent();
		// CComponent��(��) ���� ��ӵ�
		virtual void BeginPlay() override;
		virtual void Release() override;
		virtual bool TickComponent() override;
		virtual bool LastTickComponent() override;
		virtual void Render(HDC hdc) override;

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
		Maths::Vector2 m_vecGravity;
		/// <summary>
		/// ���ӵ�
		/// </summary>
		Maths::Vector2 m_vecAccelation;

		Maths::Vector2 m_vecLimitVelocity;
		Maths::Vector2 m_vecLimitGravity;

		bool m_bGround;
	};

}



