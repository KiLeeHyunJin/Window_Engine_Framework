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
		virtual void Initialize() override;
		virtual void BeginPlay() override;
		virtual void Release() override;
		virtual bool TickComponent() override;
		virtual bool LastTickComponent() override;
		virtual void Render(HDC hdc) override;

		// CColliderComponent을(를) 통해 상속됨
		const bool CheckCollision(CColliderComponent* other) override;

		const std::vector<Maths::Vector2>&	GetAxis()	const { return m_vecAxis; }
		const std::vector<Maths::Vector2>&	GetPoints() const { return m_vecPoints; }

		//friend CActor;
	private:
		std::vector<Maths::Vector2> m_vecPoints;
		std::vector<Maths::Vector2> m_vecAxis;

		// CColliderComponent을(를) 통해 상속됨

	};


}

