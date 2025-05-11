#pragma once
#include "..//WindowEngine_SOURCE//CSpriteActor.h"


namespace Framework
{
	class CBoxColliderComponent;
	class CRigidbodyComponent;
	class CTileCollisionComponent;


    class CItemActor :
        public CSpriteActor
    {
		DECLARE_PARENT(CSpriteActor)
    public:
		CItemActor(INT layer);
		virtual ~CItemActor();

		void Initialize()			override;
		void BeginPlay()			override;
		void Release()				override;
		bool Tick()					override;
		bool LastTick()				override;
		void FixedTick()			override;
		bool Render(HDC hdc) const	override;

		void OnCollisionEnter(CColliderComponent* other);
		void OnCollisionExit(CColliderComponent* other);
    private:
		float m_fRot = 0.0f;
		SHORT m_shrtRotCount = 0;
		bool m_bstandBy = false;
		bool m_bUp = false;
		FLOAT m_fYPos = 0;
		FLOAT m_fRecordY = 0;
		CBoxColliderComponent* m_pBoxColl = nullptr;
		CRigidbodyComponent* m_pRigid = nullptr;
		CTileCollisionComponent* m_pTileColl = nullptr;
    };
}


