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
		Framework::CObjectManager::InitLayerSize((UINT)eLayer::Size);
		CSceneManager::InitSceneSize((UINT)eMap::Size);

		CSceneManager::CreateScene<CDevScene>(L"DevScene", (UINT)eMap::Dev);
		CSceneManager::CreateScene<CTitleScene>(L"TitleScene", (UINT)eMap::Title);
		CSceneManager::CreateScene<CPlayScene>(L"PlayScene",(UINT)eMap::Play);


	}


	void LoadScene()
	{
		CreateScenes();
		CEventManager::LoadScene((UINT)eMap::Title);
	}



}