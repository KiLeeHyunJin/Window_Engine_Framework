#include "CTitleScene.h"

#include "CInputManager.h"
#include "CPlayScene.h"
//#include "CSceneManager.h"
#include "CUIManager.h"
#include "CEventManager.h"

#include "Object.h"
#include "CActor.h"
#include "CRenderer.h"

#include "CCameraComponent.h"
#include "CPlayerInput.h"

#include "CButton.h"
#include "CUIBase.h"

#include "ContentEnums.h"

Framework::CTitleScene::CTitleScene()
{
}

Framework::CTitleScene::~CTitleScene()
{
}

void Framework::CTitleScene::Initialize()
{
	//CActor* pCameraObj = Object::Instantiate<CActor>(Enums::eLayerType::None);
	//pCameraObj->AddComponent<CPlayerInput>();
	//CCameraComponent* pCamera = pCameraObj->AddComponent<CCameraComponent>();

	//Renderer::mainCamera = pCamera;

	//Object::Instantiate<CActor>(Enums::eLayerType::BackGround);
}

void Framework::CTitleScene::Tick()
{
}

void Framework::CTitleScene::LastTick()
{
	if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::A))
	{
		GET_SINGLE(EVENT).LoadScene((UINT)eMap::Dev, 1);
		//CSceneManager::LoadScene((UINT)eMap::Play);
	}
}

void Framework::CTitleScene::Render(HDC hdc)
{
}

void Framework::CTitleScene::Release()
{
}

void Framework::CTitleScene::OnEnter()
{
	GET_SINGLE(UI).Push(Enums::eUIType::Size);
	GET_SINGLE(UI).Push(Enums::eUIType::Button);

	CUIBase* pUI = GET_SINGLE(UI).GetUI(Enums::eUIType::Size);
	std::vector<CUIBase*> childs = pUI->GetChilds();
	if(childs.size() != 0)
	{
		CButton* btn = dynamic_cast<CButton*>(childs[0]);
		if (btn != nullptr)
		{
			btn->AddOnClickDelegate(this, &Framework::CTitleScene::Release);
		}
	}
}

void Framework::CTitleScene::OnExit()
{
	GET_SINGLE(UI).Pop(Enums::eUIType::Size);
	GET_SINGLE(UI).Pop(Enums::eUIType::Button);
}

//void Framework::CTitleScene::LastRender(HDC hdc)
//{
//}
