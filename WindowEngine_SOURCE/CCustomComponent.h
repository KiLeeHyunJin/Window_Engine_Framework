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

		bool Tick() override;
		bool LastTick() override;

		void Render(HDC hdc) override;
	};


}
