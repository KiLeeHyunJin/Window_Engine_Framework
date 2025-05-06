#pragma once
#include "..//WindowEngine_SOURCE//CSpriteActor.h"


namespace Framework
{
	class CBoxColliderComponent;
	class CRigidbodyComponent;
	class CTileCollisionComponent;


    class ItemActor :
        public CSpriteActor
    {
		DECLARE_PARENT(CSpriteActor)
    public:
		ItemActor(INT layer);
		virtual ~ItemActor();

		void Initialize()			override;
		void BeginPlay()			override;
		void Release()				override;
		bool Tick()					override;
		bool LastTick()				override;
		void FixedTick()			override;
		bool Render(HDC hdc) const	override;
    private:
		float m_fRot;
		CBoxColliderComponent* m_pBoxColl = nullptr;
		CRigidbodyComponent* m_pRigid = nullptr;
		CTileCollisionComponent* m_pTileColl = nullptr;
    };
}


