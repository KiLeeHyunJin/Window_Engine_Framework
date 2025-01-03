#include "CPlayScene.h"
#include "CGameObject.h"

#include "CTransform.h"
#include "CSpriteRenderer.h"

Framework::CPlayScene::CPlayScene()
{
}

Framework::CPlayScene::~CPlayScene()
{
}

void Framework::CPlayScene::Initialize()
{
	CGameObject* obj = new CGameObject();
	obj->AddComponent<CTransform>()->SetPos(Vector2(200,200));
	CSpriteRenderer* pRender = obj->AddComponent<CSpriteRenderer>();
	pRender->ImageLoad(L"Resources\\Room.png");
	AddGameObject(obj);

}

void Framework::CPlayScene::Tick()
{
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
