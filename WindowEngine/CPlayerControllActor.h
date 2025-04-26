#pragma once
#include "CActor.h"

//#include "..//WindowEngine_SOURCE//CActor.h"
namespace Framework
{
	class CPlayerControllActor :
		public CActor
	{
		DECLARE_PARENT(CActor)
	public:
		CPlayerControllActor(UINT layer);

		// CActor을(를) 통해 상속됨
		void BeginPlay()			override;
		void Release()				override;

		bool Tick()					override;
		bool LastTick()				override;
		void FixedTick()			override;

		bool Render(HDC hdc) const	override;
	private:
		virtual void OnCollisionEnter(CColliderComponent* other);
		virtual void OnCollisionStay(CColliderComponent* other);
		virtual void OnCollisionExit(CColliderComponent* other);

		uint32_t collChecking		= 0;
		Color m_color;
		//uint32_t collChecking2;


		// CActor을(를) 통해 상속됨


		// CActor을(를) 통해 상속됨
		void Initialize() override;

	};


}
