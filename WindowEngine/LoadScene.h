#pragma once

#include "..\\WindowEngine_SOURCE\\CSceneManager.h"
#include "CPlayScene.h"
#include "CTitleScene.h"

namespace Framework
{
	void LoadScenes()
	{
		CSceneManager::CreateScene<CPlayScene>(L"PlayScene");
		CSceneManager::CreateScene<CTitleScene>(L"TitleScene");

		//CSceneManager::CreateScene(L"PlayeScene", new CPlayeScene); //씬은 씬매니저가 생성하게하자

		CSceneManager::LoadScene(L"TitleScene");
	}

}