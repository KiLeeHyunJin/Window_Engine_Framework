#include "CTitleScene.h"

#include "CInputManager.h"
#include "CPlayScene.h"
#include "CSceneManager.h"
#include "CObject.h"

Framework::CTitleScene::CTitleScene()
{
}

Framework::CTitleScene::~CTitleScene()
{
}

void Framework::CTitleScene::Initialize()
{
	Object::Instantiate<CGameObject>(eLayerType::BackGround);
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
}

void Framework::CTitleScene::Release()
{
}

void Framework::CTitleScene::OnEnter()
{
}

void Framework::CTitleScene::OnExit()
{
}
