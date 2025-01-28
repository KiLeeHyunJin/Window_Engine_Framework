#pragma once
#include "CColliderComponent.h"

namespace Framework
{
	class CGameObject;
	class CBoxColliderComponent :
		public CColliderComponent
	{
	public:

		friend CGameObject;
	private:
		CBoxColliderComponent();
		virtual ~CBoxColliderComponent();

		// CComponent��(��) ���� ��ӵ�
		virtual void Initialize() override;
		virtual void Release() override;
		virtual void Tick() override;
		virtual void LastTick() override;
		virtual void Render(HDC hdc) override;

		//Maths::Vector2 m_vecSize;

	};


}

