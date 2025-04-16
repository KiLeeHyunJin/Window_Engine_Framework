#include "CDevScene.h"

#include "CTilemap.h"
#include "CTilemapActor.h"
#include "Object.h"
#include "CResourceManager.h"

#include "CPlayerControllActor.h"
#include "CSpriteActor.h"

#include "CRigidbodyComponent.h"
#include "CBoxColliderComponent.h"
#include "ContentsEnums.h"
#include "CCameraComponent.h"
#include "CRenderer.h"
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


		 CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
		 if (pCam == nullptr) // Create Camera
		 {
			 CActor* pActor = Object::Instantiate<CSpriteActor>(static_cast<UINT>(eLayer::Character), L"Test2");
			 pCam = pActor->AddComponent<CCameraComponent>();
			 Renderer::CRenderer::SetMainCamera(pCam);

			 const Maths::Vector2 vecMin(-2048, 2048);
			 const Maths::Vector2 vecMax(2048, -2048);
			 pCam->SetCameraRange(vecMin, vecMax);

			 const Maths::Vector2 vecFollowMin(-100, 100);
			 const Maths::Vector2 vecFollowMax(100, -100);
			 pCam->SetFollowRange(vecFollowMin, vecFollowMax);
		 }

		 CActor* pActor = Object::Instantiate<CPlayerControllActor>(static_cast<UINT>(eLayer::Character), L"Test");
		 {
			 pActor->AddComponent<CRigidbodyComponent>();
			 CBoxColliderComponent* pBoxColl = pActor->AddComponent<CBoxColliderComponent>();
			 pBoxColl->AddCollisionFlag((UINT)eLayer::Character);
			 pBoxColl->SetSize(Maths::Vector2(50, 50));
			 pActor->SetPosition(Maths::Vector2(50, 50));
		 }

		 pCam->SetTarget(pActor);

		 {
			 CTilemapActor* ta = Object::Instantiate<CTilemapActor>(3, L"");
			 SetTilemapActor(ta);
			 CTilemap* tm = GET_SINGLE(RESOURCE).CreateTilemap(L"Dev");
			 tm->SetMapSize(Maths::Vector2(48, 63));
			 tm->SetTileSize(48);
			 ta->SetTilemap(tm);
			 ta->SetShowDebug(true);
		 }



	}
	void CDevScene::OnExit()
	{
		//SAFE_DELETE(m_pTilemapActor);
	}
	//void CDevScene::LastRender(HDC hdc)
	//{
	//}
}
