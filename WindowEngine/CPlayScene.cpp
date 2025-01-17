#include "CPlayScene.h"
#include "..\\WindowEngine_SOURCE\\CObject.h"

#include "CInputManager.h"
#include "CSceneManager.h"
#include "CResourceManager.h"

#include "CTransformComponent.h"
#include "CSpriteRendererComponent.h"
#include "CCameraComponent.h"
#include "CAnimatorComponent.h"

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
	CGameObject* pObj = Object::Instantiate<CGameObject>(Enums::eLayerType::BackGround);
	CTransformComponent* pTr = pObj->AddComponent<CTransformComponent>();
	CTexture* pTexture = Framework::CResourceManager::Find<CTexture>(L"Room");
	CAnimatorComponent* pAnim = pObj->AddComponent<CAnimatorComponent>();
	pAnim->CreateAnimation(L"Room", pTexture,Vector2::Zero, Vector2(50,50), Vector2::Zero, 5, 0.2f );
	pAnim->PlayAnimation(L"Room", true);

	CGameObject* pCameraObj = Object::Instantiate<CGameObject>(Enums::eLayerType::None);
	pCameraObj->AddComponent<CPlayerInput>();
	CCameraComponent* pCamera = pCameraObj->AddComponent<CCameraComponent>();
	
	Renderer::mainCamera = pCamera;
	pCamera->SetTarget(pObj);

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
