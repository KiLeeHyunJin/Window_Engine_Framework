#include "CPlayeScene.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CSpriteRenderer.h"

Framework::CPlayeScene::CPlayeScene()
{
}

Framework::CPlayeScene::~CPlayeScene()
{
}

void Framework::CPlayeScene::Initialize()
{
	CGameObject* obj = new CGameObject();
	obj->AddComponent<CTransform>()->SetPos(200,300);
	obj->AddComponent<CSpriteRenderer>();

	AddGameObject(obj);

	CScene::Initialize();
}

void Framework::CPlayeScene::Tick()
{
	CScene::Tick();
}

void Framework::CPlayeScene::LastTick()
{
	CScene::LastTick();
}

void Framework::CPlayeScene::Render(HDC hDC)
{
	CScene::Render(hDC);
}

void Framework::CPlayeScene::Release()
{
	CScene::Tick();

}
