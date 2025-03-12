#pragma once

#include "..\\WindowEngine_SOURCE\\CSceneManager.h"
//#include "..\\WindowEngine_SOURCE\\CDontDestroyOnLoad.h"

#include "CPlayScene.h"
#include "CTitleScene.h"
#include "MapEnums.h"

namespace Framework
{
	void CreateScenes()
	{
		CSceneManager::InitMapDataSize((UINT)eMap::Size);

		CSceneManager::CreateScene<CPlayScene>(L"PlayScene",(UINT)eMap::Play);
		CSceneManager::CreateScene<CTitleScene>(L"TitleScene", (UINT)eMap::Title);
	}


	void LoadScene()
	{
		CreateScenes();

		//CSceneManager::LoadScene((UINT)eMap::Title);
	}



}