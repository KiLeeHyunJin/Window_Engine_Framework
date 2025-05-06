#include "CDevScene.h"

#include "CPlayerCharacterActor.h"
#include "CSpriteActor.h"
#include "CTileActor.h"

#include "CTilemapActor.h"

#include "Object.h"
#include "CRenderer.h"
#include "ContentEnums.h"

#include "CResourceManager.h"
#include "CCollisionManager.h"

#include "CBoxColliderComponent.h"
#include "CCameraComponent.h"

namespace Framework
{
	CDevScene::CDevScene()
	{
	}
	CDevScene::~CDevScene()
	{
	}
	void CDevScene::LoadFile(const std::wstring& path)
	{
	}
	void CDevScene::SaveFile(const std::wstring& path)
	{
	}
	void CDevScene::SetTilemapActor(CActor* actor)
	{
		CTilemapActor* ta = dynamic_cast<CTilemapActor*>(actor);
		if (ta != nullptr)
		{
			m_pTilemapActor = ta;
		}

	}
	void CDevScene::Initialize()
	{
	}
	void CDevScene::Tick()
	{
	}
	void CDevScene::LastTick()
	{
	}
	void CDevScene::Render(HDC hdc)
	{
	}
	void CDevScene::Release()
	{
	}
	void CDevScene::OnEnter()
	{
		GET_SINGLE(COLLISION).SetCollisionLayerState((UINT)eLayer::Item		, (UINT)eLayer::Character	, true);
		GET_SINGLE(COLLISION).SetCollisionLayerState((UINT)eLayer::Monster	, (UINT)eLayer::Character	, true);
		GET_SINGLE(COLLISION).SetCollisionLayerState((UINT)eLayer::Tile		, (UINT)eLayer::Character	, true);

		GET_SINGLE(COLLISION).SetCollisionLayerState((UINT)eLayer::Tile		, (UINT)eLayer::Tile		, false);
		GET_SINGLE(COLLISION).SetCollisionLayerState((UINT)eLayer::Character, (UINT)eLayer::Character	, false);

#pragma region  Cam

		CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();

		if (pCam == nullptr) // Create Camera
		{
			CActor* pActor = Object::Instantiate<CSpriteActor>(static_cast<UINT>(eLayer::Character), L"Cam");
			pCam = pActor->AddComponent<CCameraComponent>();
			Renderer::CRenderer::SetMainCamera(pCam);

			const Maths::Vector2 vecMax(2048, 2048);
			pCam->SetCameraRange(vecMax);

			const Maths::Vector2 vecFollowMin(-100, 100);
			const Maths::Vector2 vecFollowMax(100, -100);
			pCam->SetFollowRange(vecFollowMin, vecFollowMax);
		}

#pragma endregion


#pragma region  TileMapActor
		if (false)
		{
			CTilemapActor* ta = Object::Instantiate<CTilemapActor>(3, L"");
			SetTilemapActor(ta);
			CTilemap* tm = GET_SINGLE(RESOURCE).CreateTilemap(L"Dev");
			tm->SetMapSize(Maths::Vector2(48, 63));
			tm->SetTileSize(24);
			ta->SetTilemap(tm);
			ta->SetShowDebug(true);
		}
#pragma endregion

	
#pragma region  Player
		{
			CActor* pActor = Object::Instantiate<CPlayerCharacterActor>(static_cast<UINT>(eLayer::Character), L"Player");

			pActor->SetLocalPosition(Maths::Vector2(0, 0));
			pActor->SetScale(Maths::Vector2(20, 20));
			pCam->SetTarget(pActor);
		}

#pragma endregion

		{
			CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Tile1");

			pActor->SetLocalPosition(Maths::Vector2(100, 500));
			pActor->SetScale(Maths::Vector2(20, 20));
			pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(96, 15));
		}

		//{
		//	CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Test3");
		//	pActor->SetLocalPosition(Maths::Vector2(100, 650));
		//	pActor->SetScale(Maths::Vector2(20, 20));
		//	pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(96, 15));
		//}

		//{
		//	CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Test3");
		//	pActor->SetLocalPosition(Maths::Vector2(100, 750));
		//	pActor->SetScale(Maths::Vector2(20, 20));
		//	pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(96, 15));
		//}

		//{
		//	CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Test2");

		//	pActor->SetLocalPosition(Maths::Vector2(190, 530));
		//	pActor->SetScale(Maths::Vector2(20, 20));
		//	pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(96, 15));
		//}





		//{
		//	CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Test2");

		//	pActor->SetLocalPosition(Maths::Vector2(160, 570));
		//	pActor->SetScale(Maths::Vector2(20, 20));
		//	pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(96, 15));
		//}


		//{
		//	CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Test2");

		//	pActor->SetLocalPosition(Maths::Vector2(190, 700));
		//	pActor->SetScale(Maths::Vector2(20, 20));
		//	pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(96, 15));
		//}


		//{
		//	CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Test2");

		//	pActor->SetLocalPosition(Maths::Vector2(210, 750));
		//	pActor->SetScale(Maths::Vector2(20, 20));
		//	pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(96, 15));
		//}
		//{
		//	CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Test2");

		//	pActor->SetLocalPosition(Maths::Vector2(300, 770));
		//	pActor->SetScale(Maths::Vector2(20, 20));
		//	pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(96, 15));
		//	//pActor->GetComponent<CBoxColliderComponent>()->SetAngle(20);
		//}

		//{
		//	CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Test2");

		//	pActor->SetLocalPosition(Maths::Vector2(190, 800));
		//	pActor->SetScale(Maths::Vector2(20, 20));
		//	pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(96, 15));
		//}


		//{
		//	CActor* pActor = Object::Instantiate<CTileActor>(static_cast<UINT>(eLayer::Tile), L"Test2");

		//	pActor->SetLocalPosition(Maths::Vector2(200, 830));
		//	pActor->SetScale(Maths::Vector2(20, 20));
		//	pActor->GetComponent<CBoxColliderComponent>()->SetSize(Maths::Vector2(192, 15));
		//}

	}
	void CDevScene::OnExit()
	{

	}
}
