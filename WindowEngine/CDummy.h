#pragma once
#include "CommonInclude.h"
#include "CCustomComponent.h"
#include "Structs.h"

namespace Framework
{
	class CDummy :
		public CCustomComponent
	{
	public: 
		void Initialize() override;
		void Release() override;

		void Tick() override;
		void Render(HDC hdc) override;

		virtual void OnCollisionEnter(CColliderComponent* other) override;
		virtual void OnCollisionStay(CColliderComponent* other) override;
		virtual void OnCollisionExit(CColliderComponent* other) override;
	private:
		Color m_colorFill;
	};
}


