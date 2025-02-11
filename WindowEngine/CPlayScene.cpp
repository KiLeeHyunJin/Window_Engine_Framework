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

Framework::CPlayScene::CPlayScene()
{
}

Framework::CPlayScene::~CPlayScene()
{
}

void Framework::CPlayScene::Initialize()
{
	CTexture* pTexture = Framework::CResourceManager::Find<CTexture>(L"Room");


	CGameObject* pObj = Object::Instantiate<CPlayerInput>(Enums::eLayerType::BackGround, L"pObj")->GetOwner();
	CBoxColliderComponent* pBoxColl = pObj->AddComponent<CBoxColliderComponent>();
	CRigidbodyComponent* pRigid = pObj->AddComponent<CRigidbodyComponent>();
	pRigid->SetGround(true);

	CPlayerInput* pInput = pObj->AddComponent<CPlayerInput>();
	pObj->GetTransformComponent()->SetPos(Maths::Vector2(100, 100));

	//CAnimatorComponent* pAnim = pObj->AddComponent<CAnimatorComponent>();
	//pAnim->CreateAnimation(L"Room", pTexture, Vector2::Zero, Vector2(50, 50), Vector2::Zero, 5, 0.2f);
	//pAnim->PlayAnimation(L"Room", true);


	pObj = Object::Instantiate<CPlayerInput>(Enums::eLayerType::BackGround, L"pObj")->GetOwner();
	pBoxColl = pObj->AddComponent<CBoxColliderComponent>();
	pRigid = pObj->AddComponent<CRigidbodyComponent>();
	pRigid->SetGround(true);
	pObj->AddComponent<CPlayerInput>();
	pObj->GetTransformComponent()->SetPos(Maths::Vector2(100, 100));

	CCollisionManager::SetCollisionLayerState(Enums::eLayerType::BackGround, Enums::eLayerType::BackGround, true);


	//pObj->AddComponent<CPlayerInput>();


	CGameObject* pCameraObj = Object::Instantiate(Enums::eLayerType::None, L"Cam");
	
	CCameraComponent* pCamera = pCameraObj->AddComponent<CCameraComponent>();

	Object::DontDestoryOnLoad(pCameraObj);
	
	Renderer::CRenderer::SetMainCamera(pCamera);
	//pCamera->SetTarget(pObj);

	//pSr->ImageLoad(L"Resources\\Room.png");
}

void Framework::CPlayScene::Tick()
{
	if (INPUT::GetKeyDown(eKeyCode::A))
	{
		CSceneManager::LoadScene(L"PlayScene");
	}
}

void Framework::CPlayScene::LastTick()
{
}

void Framework::CPlayScene::Render(HDC hdc)
{
	wchar_t str[50] = L"PlayScene";
	int len = (int)wcsnlen_s(str, 50);

	TextOut(hdc, 0, 0, str, len);
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
