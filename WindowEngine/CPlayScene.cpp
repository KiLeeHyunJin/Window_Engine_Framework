#include "CPlayScene.h"
#include "..\\WindowEngine_SOURCE\\CObject.h"

#include "CInputManager.h"
#include "CSceneManager.h"
#include "CResourceManager.h"
#include "CCollisionManager.h"

#include "CTransformComponent.h"
#include "CSpriteRendererComponent.h"
#include "CCameraComponent.h"
#include "CAnimatorComponent.h"
#include "CBoxColliderComponent.h"
#include "CRigidbodyComponent.h"


#include "CGameObject.h"
#include "CRenderer.h"

#include "CTexture.h"
#include "CPlayerInput.h"
#include "CDummy.h"
#include "MapEnums.h"

Framework::CPlayScene::CPlayScene()
{
}

Framework::CPlayScene::~CPlayScene()
{
}

void Framework::CPlayScene::Initialize()
{
	CTexture* pTexture = Framework::CResourceManager::Find<CTexture>(L"Room");


	CGameObject* pObj = Object::Instantiate<CPlayerInput>((UINT)Enums::eLayerType::BackGround, L"Player")->GetOwner();
	CBoxColliderComponent* pBoxColl = pObj->AddComponent<CBoxColliderComponent>();
	CRigidbodyComponent* pRigid = pObj->AddComponent<CRigidbodyComponent>();
	pRigid->SetGround(true);

	//CPlayerInput* pInput = pObj->AddComponent<CPlayerInput>();
	pObj->GetTransformComponent()->SetPos(Maths::Vector2(100, 100));

	//CAnimatorComponent* pAnim = pObj->AddComponent<CAnimatorComponent>();
	//pAnim->CreateAnimation(L"Room", pTexture, Vector2::Zero, Vector2(50, 50), Vector2::Zero, 5, 0.2f);
	//pAnim->PlayAnimation(L"Room", true);


	pObj = Object::Instantiate<CDummy>((UINT)Enums::eLayerType::BackGround, L"Dummy")->GetOwner();
	pBoxColl = pObj->AddComponent<CBoxColliderComponent>();
	pRigid = pObj->AddComponent<CRigidbodyComponent>();
	pRigid->SetGround(true);
	//pObj->AddComponent<CPlayerInput>();
	pObj->GetTransformComponent()->SetPos(Maths::Vector2(100, 100));

	CCollisionManager::SetCollisionLayerState((UINT)Enums::eLayerType::BackGround, (UINT)Enums::eLayerType::BackGround, true);


	//pObj->AddComponent<CPlayerInput>();


	CGameObject* pCameraObj = Object::Instantiate((UINT)Enums::eLayerType::None, L"Cam");
	
	CCameraComponent* pCamera = pCameraObj->AddComponent<CCameraComponent>();

	Object::DontDestoryOnLoad(pCameraObj);
	
	Renderer::CRenderer::SetMainCamera(pCamera);
	//pCamera->SetTarget(pObj);

	//pSr->ImageLoad(L"Resources\\Room.png");
}

void Framework::CPlayScene::Tick()
{
	if (INPUT::GetKeyDown(eKeyCode::B))
	{
		EVENT::LoadScene((UINT)eMap::Title, 1);
	}
}

void Framework::CPlayScene::LastTick()
{
}

void Framework::CPlayScene::Render(HDC hdc)
{
}

void Framework::CPlayScene::Release()
{
}

void Framework::CPlayScene::OnEnter()
{
}

void Framework::CPlayScene::OnExit()
{
}
