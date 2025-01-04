#include "CPlayScene.h"
#include "CGameObject.h"
#include "CInputManager.h"
#include "CSceneManager.h"
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
	CGameObject* pObj = new CGameObject();
	CTransform*		 pTs = pObj->AddComponent<CTransform>();
	CSpriteRenderer* pSr = pObj->AddComponent<CSpriteRenderer>();

	pTs->SetPos(Vector2(200, 200));
	pSr->ImageLoad(L"Resources\\Room.png");

	AddGameObject(pObj, eLayerType::BackGround);

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
