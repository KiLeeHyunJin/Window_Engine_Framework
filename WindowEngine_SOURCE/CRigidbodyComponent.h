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
		// CComponent��(��) ���� ��ӵ�
		virtual void Initialize() override;
		virtual void Release() override;
		virtual void Tick() override;
		virtual void LastTick() override;
		virtual void Render(HDC hdc) override;

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

	};

}


