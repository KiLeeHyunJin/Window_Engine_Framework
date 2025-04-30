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

		bool TileAdjustPosition(CBoxColliderComponent* targetCollider);
	protected:
		// CActor을(를) 통해 상속됨
		void Initialize()			override;

		void BeginPlay()			override;
		void Release()				override;

		bool Tick()					override;
		bool LastTick()				override;
		void FixedTick()			override;

		bool Render(HDC hdc) const	override;

		virtual void OnCollisionEnter(CColliderComponent* other) override;
		virtual void OnCollisionStay(CColliderComponent* other)  override;

	private:
		bool CheckCollisionLine(const CBoxColliderComponent* target);

		CBoxColliderComponent*	m_pBoxCollider		= nullptr;
		CRigidbodyComponent*	m_pRigidbody		= nullptr;
		CLineComponent*			m_pLine				= nullptr;
	};

}

