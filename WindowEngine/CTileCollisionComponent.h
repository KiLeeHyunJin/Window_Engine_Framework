#pragma once
#include "..//WindowEngine_SOURCE//CCustomComponent.h"

namespace Framework
{
	class CTileActor;
	class CBoxColliderComponent;
	class CRigidbodyComponent;

    class CTileCollisionComponent :
        public CCustomComponent
    {
	public:
		CTileCollisionComponent();
		virtual ~CTileCollisionComponent();

		void AddTile(CTileActor* pTile) { m_vecTiles.push_back(pTile); }
		void RemoveTile(CTileActor* pTile)
		{
			auto iter = std::remove(m_vecTiles.begin(), m_vecTiles.end(), pTile);
			m_vecTiles.erase(iter);
		};

		void BeginPlay() override;
		void Release() override;

		bool TickComponent() override;
		bool LastTickComponent() override;

		void Render(HDC hdc) override;

		// CComponent을(를) 통해 상속됨
		void FixedComponent() override;

	private:
		std::vector<CTileActor*> m_vecTiles;
		CBoxColliderComponent* m_pBoxColl = nullptr;
		CRigidbodyComponent* m_pRigid = nullptr;
    };
}


