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
		Enums::eComponentType GetComponentType() const override { return StaticComponentType(); }

		friend CGameObject;
		friend CColliderComponent;
	private:
		virtual void OnCollisionEnter(CColliderComponent* other);
		virtual void OnCollisionStay(CColliderComponent* other);
		virtual void OnCollisionExit(CColliderComponent* other);

		void Initialize() override;
		void Release() override;

		void Tick() override;
		void LastTick() override;

		void Render(HDC hdc) override;
	};


}
