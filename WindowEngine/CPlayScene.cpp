#include "CPlayScene.h"
#include "CGameObject.h"
#include "CInputManager.h"
#include "CSceneManager.h"
#include "CTransformComponent.h"
#include "CSpriteRendererComponent.h"
#include "CTexture.h"
#include "..\\WindowEngine_SOURCE\\CObject.h"
#include "CCameraComponent.h"
#include "CPlayerInput.h"
#include "CRenderer.h"

Framework::CPlayScene::CPlayScene()
{
}

Framework::CPlayScene::~CPlayScene()
{
}

void Framework::CPlayScene::Initialize()
{
	CGameObject* pCameraObj = Object::Instantiate<CGameObject>(Enums::eLayerType::None);
	CCameraComponent* pCamera = pCameraObj->AddComponent<CCameraComponent>();
	Renderer::mainCamera = pCamera;
	pCameraObj->AddComponent<CPlayerInput>();
	CGameObject* pObj = new CGameObject();
	CTransformComponent*		 pTs = pObj->AddComponent<CTransformComponent>();
	pCamera->SetTarget(pObj);
	pObj->AddComponent<CSpriteRendererComponent>() ->SetTexture(L"Room");
	pTs->SetPos(Maths::Vector2(200, 200));
	//pSr->ImageLoad(L"Resources\\Room.png");

	AddGameObject(pObj, Enums::eLayerType::BackGround);

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
	//obj->GetComponent<CTransform>()->SetPos(Vector2(0, 0));
}
