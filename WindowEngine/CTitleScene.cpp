#include "CTitleScene.h"

#include "CInputManager.h"
#include "CUIManager.h"

#include "Object.h"
#include "CRenderer.h"

#include "CCameraComponent.h"

#include "CGameControllActor.h"


#include "CButton.h"
#include "CUIBase.h"

#include "CPlayScene.h"

#include "ContentEnums.h"

Framework::CTitleScene::CTitleScene()
{
}

Framework::CTitleScene::~CTitleScene()
{
}

void Framework::CTitleScene::Initialize()
{
	Object::Instantiate<CGameControllActor>	((UINT)eLayer::None	,L"GameManager"	,true);	//GameManager


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
