#include "CDevScene.h"

#include "CTilemap.h"
#include "CTilemapActor.h"

#include "Object.h"
#include "CRenderer.h"
#include "ContentEnums.h"

#include "CResourceManager.h"
#include "CCollisionManager.h"

#include "CPlayerControllActor.h"
#include "CSpriteActor.h"

#include "CRigidbodyComponent.h"
#include "CBoxColliderComponent.h"
#include "CCameraComponent.h"
#include "CLineComponent.h"

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
		GET_SINGLE(COLLISION).SetCollisionLayerState((UINT)eLayer::Character, (UINT)eLayer::Character, true);
		//GET_SINGLE(COLLISION).SetCollisionLayerState((UINT)eLayer::Character, (UINT)eLayer::Environment, true);

		CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
		if (pCam == nullptr) // Create Camera
		{
			CActor* pActor = Object::Instantiate<CSpriteActor>(static_cast<UINT>(eLayer::Character), L"Test2");
			pCam = pActor->AddComponent<CCameraComponent>();
			Renderer::CRenderer::SetMainCamera(pCam);

			const Maths::Vector2 vecMax(2048, 2048);
			pCam->SetCameraRange(vecMax);

			const Maths::Vector2 vecFollowMin(-100, 100);
			const Maths::Vector2 vecFollowMax(100, -100);
			pCam->SetFollowRange(vecFollowMin, vecFollowMax);
		}


		if(false)
		{
			CTilemapActor* ta = Object::Instantiate<CTilemapActor>(3, L"");
			SetTilemapActor(ta);
			CTilemap* tm = GET_SINGLE(RESOURCE).CreateTilemap(L"Dev");
			tm->SetMapSize(Maths::Vector2(48, 63));
			tm->SetTileSize(24);
			ta->SetTilemap(tm);
			ta->SetShowDebug(true);
		}


		{
			CActor* pActor = Object::Instantiate<CPlayerControllActor>(static_cast<UINT>(eLayer::Character), L"Test");

			pActor->SetPosition(Maths::Vector2(0, 0));
			pActor->SetScale(Maths::Vector2(20, 20));

			CRigidbodyComponent*	pRigid		= pActor->AddComponent<CRigidbodyComponent>();
			CBoxColliderComponent*	pBoxColl	= pActor->AddComponent<CBoxColliderComponent>();
			
			//pBoxColl->RemoveCollisionFlag((UINT)eLayer::Character);
			pBoxColl->SetSize(Maths::Vector2(40, 70));
			//pBoxColl->SetAngle(20);
			pBoxColl->SetTrigger(false);
			pBoxColl->Initialize();
			pCam->SetTarget(pActor);
		}
		return;
		{
			CActor* pActor = Object::Instantiate<CSpriteActor>(static_cast<UINT>(eLayer::Character), L"Test");

			pActor->SetPosition(Maths::Vector2(100, 100));
			pActor->SetScale(Maths::Vector2(20, 20));

			CRigidbodyComponent* pRigid = pActor->AddComponent<CRigidbodyComponent>();
			CBoxColliderComponent* pBoxColl = pActor->AddComponent<CBoxColliderComponent>();
			CLineComponent* pLine = pActor->AddComponent<CLineComponent>();

			pBoxColl->AddCollisionFlag((UINT)eLayer::Character);
			pBoxColl->SetSize(Maths::Vector2(96, 48));
			pBoxColl->SetAngle(10);
			pBoxColl->SetTrigger(false);
			pBoxColl->Initialize();

			pLine->SetLineHeightPercent(0.1f);
			pLine->Initialize();

			//pCam->SetTarget(pActor);
		}

		//for (UINT i = 200; i > 0; i--)
		//{
		//	CActor* pActor = Object::Instantiate<CSpriteActor>(static_cast<UINT>(eLayer::Character), L"Test" + std::to_wstring(i));

		//	pActor->AddComponent<CRigidbodyComponent>();
		//	CBoxColliderComponent* pBoxColl = pActor->AddComponent<CBoxColliderComponent>();
		//	pBoxColl->AddCollisionFlag((UINT)eLayer::Character);
		//	pBoxColl->SetSize(Maths::Vector2(50, 50));
		//	pActor->SetPosition(Maths::Vector2Int(150 + (i), 50 + i));
		//	pBoxColl->SetTrigger(false);

		//	pCam->SetTarget(pActor);
		//}


	}
	void CDevScene::OnExit()
	{
		//SAFE_DELETE(m_pTilemapActor);
	}
	//void CDevScene::LastRender(HDC hdc)
	//{
	//}
}
