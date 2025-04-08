#pragma once

#include "..\\WindowEngine_SOURCE\\CSceneManager.h"
#include "..\\WindowEngine_SOURCE\\CEventManager.h"
//#include "..\\WindowEngine_SOURCE\\CDontDestroyOnLoad.h"
#include "..\\WindowEngine_SOURCE\\CObjectManager.h"

#include "CPlayScene.h"
#include "CTitleScene.h"
#include "CDevScene.h"

#include "ContentsEnums.h"
#include "..\\WindowEngine_SOURCE\\Enums.h"

namespace Framework
{
	void CreateScenes()
	{
		OBJECT::InitLayerSize((UINT)eLayer::Size);
		SCENE::InitSceneSize((UINT)eMap::Size);

		SCENE::CreateScene<CDevScene>(L"DevScene", (UINT)eMap::Dev);
		SCENE::CreateScene<CTitleScene>(L"TitleScene", (UINT)eMap::Title);
		SCENE::CreateScene<CPlayScene>(L"PlayScene",(UINT)eMap::Play);


	}


	void LoadScene()
	{
		CreateScenes();
		EVENT::LoadScene((UINT)eMap::Title);
	}



}