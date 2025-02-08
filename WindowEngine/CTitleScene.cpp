#include "CTitleScene.h"

#include "CInputManager.h"
#include "CPlayScene.h"
#include "CSceneManager.h"
#include "CUIManager.h"

#include "CObject.h"
#include "CGameObject.h"
#include "CRenderer.h"

#include "CCameraComponent.h"
#include "CPlayerInput.h"

#include "CButton.h"
#include "CUIBase.h"

Framework::CTitleScene::CTitleScene()
{
}

Framework::CTitleScene::~CTitleScene()
{
}

void Framework::CTitleScene::Initialize()
{
	//CGameObject* pCameraObj = Object::Instantiate<CGameObject>(Enums::eLayerType::None);
	//pCameraObj->AddComponent<CPlayerInput>();
	//CCameraComponent* pCamera = pCameraObj->AddComponent<CCameraComponent>();

	//Renderer::mainCamera = pCamera;

	//Object::Instantiate<CGameObject>(Enums::eLayerType::BackGround);
	
}

void Framework::CTitleScene::Tick()
{
}

void Framework::CTitleScene::LastTick()
{
	if (INPUT::GetKeyDown(eKeyCode::A))
	{
		CSceneManager::LoadScene(L"PlayScene");
	}
}

void Framework::CTitleScene::Render(HDC hdc)
{
	wchar_t str[50] = L"TitleScene";
	int len = (int)wcsnlen_s(str, 50);

	TextOut(hdc, 200, 200, str, len);
	Maths::Vector2 mousePos = CInputManager::GetMousePosition();


}

void Framework::CTitleScene::Release()
{
}

void Framework::CTitleScene::OnEnter()
{
	UI::Push(Enums::eUIType::Size);
	UI::Push(Enums::eUIType::Button);
}

void Framework::CTitleScene::OnExit()
{
	UI::Pop(Enums::eUIType::Size);
	UI::Pop(Enums::eUIType::Button);
}
