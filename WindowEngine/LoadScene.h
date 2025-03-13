#pragma once

#include "..\\WindowEngine_SOURCE\\CSceneManager.h"
#include "..\\WindowEngine_SOURCE\\CEventManager.h"
//#include "..\\WindowEngine_SOURCE\\CDontDestroyOnLoad.h"

#include "CPlayScene.h"
#include "CTitleScene.h"
#include "MapEnums.h"

namespace Framework
{
	void CreateScenes()
	{
		CSceneManager::InitMapDataSize((UINT)eMap::Size);

		CSceneManager::CreateScene<CTitleScene>(L"TitleScene", (UINT)eMap::Title);
		CSceneManager::CreateScene<CPlayScene>(L"PlayScene",(UINT)eMap::Play);


	}


	void LoadScene()
	{
		CreateScenes();
		CEventManager::LoadScene((UINT)eMap::Title);
	}



}