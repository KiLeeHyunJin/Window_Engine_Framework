#pragma once
#include "CComponent.h"

namespace Framework
{
	class CColliderComponent;

	class CCustomComponent : public CComponent
	{

	protected:
		CCustomComponent();
		virtual ~CCustomComponent();

		static constexpr Enums::eComponentType StaticComponentType() { return Enums::eComponentType::Custom; }
		const Enums::eComponentType GetComponentType() const override { return StaticComponentType(); }

		friend CActor;
		friend CColliderComponent;
	private:
		virtual void OnCollisionEnter(CColliderComponent* other);
		virtual void OnCollisionStay(CColliderComponent* other);
		virtual void OnCollisionExit(CColliderComponent* other);

		void BeginPlay() override;
		void Release() override;

		bool TickComponent() override;
		bool LastTickComponent() override;

		void Render(HDC hdc) override;

		// CComponent을(를) 통해 상속됨
		void FixedComponent() override;
	};


}
