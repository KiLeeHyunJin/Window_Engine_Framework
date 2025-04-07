#pragma once
#include "..\\WindowEngine_SOURCE\\CCustomComponent.h"
#include "..\\WindowEngine_SOURCE\\CRenderManager.h"
#include "..\\WindowEngine_SOURCE\\Structs.h"

namespace Framework
{
	class CPlayerInput :
		public CCustomComponent
	{
	public:
		CPlayerInput();
		virtual ~CPlayerInput();

	private:
		void BeginPlay() override;
		void Release() override;

		bool TickComponent() override;
		bool LastTickComponent() override;

		void Render(HDC hdc) override;

		virtual void OnCollisionEnter(CColliderComponent* other) override;
		virtual void OnCollisionStay(CColliderComponent* other) override;
		virtual void OnCollisionExit(CColliderComponent* other) override;

		Color m_colorFill;
		int id;
		static int temp;
	};


}
