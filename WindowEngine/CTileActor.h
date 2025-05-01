#pragma once
#include "..//WindowEngine_SOURCE//CSpriteActor.h"

namespace Framework
{
	class CBoxColliderComponent;
	class CRigidbodyComponent;
	class CLineComponent;

	class CTileActor :
		public CSpriteActor
	{
		DECLARE_PARENT(CSpriteActor)
	public:
		CTileActor(UINT layer);
		virtual ~CTileActor();

		bool CheckCollisionLine(const CBoxColliderComponent* target, float& lineY);
		void GetPositionY(float x, float& y);
	protected:
		// CActor을(를) 통해 상속됨
		void Initialize()			override;

		void BeginPlay()			override;
		void Release()				override;

		bool Tick()					override;
		bool LastTick()				override;
		void FixedTick()			override;

		bool Render(HDC hdc) const	override;


	private:

		CBoxColliderComponent*	m_pBoxCollider		= nullptr;
		CRigidbodyComponent*	m_pRigidbody		= nullptr;
		CLineComponent*			m_pLine				= nullptr;
	};

}

