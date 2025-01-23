#pragma once

#include "..\\WindowEngine_SOURCE\\CSceneManager.h"
#include "..\\WindowEngine_SOURCE\\CDontDestroyOnLoad.h"

#include "CPlayScene.h"
#include "CTitleScene.h"

namespace Framework
{
	void CreateScenes()
	{
		CSceneManager::CreateScene<CPlayScene>(L"PlayScene");
		CSceneManager::CreateScene<CTitleScene>(L"TitleScene");
	}


	void LoadScene()
	{
		CreateScenes();

		CSceneManager::LoadScene(L"TitleScene");
	}



}