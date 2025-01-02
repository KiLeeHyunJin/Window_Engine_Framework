#pragma once

#include "..\\WindowEngine_SOURCE\\CSceneManager.h"
#include "CPlayeScene.h"

namespace Framework
{
	void LoadScenes()
	{
		CSceneManager::CreateScene<CPlayeScene>(L"PlayeScene");

		//CSceneManager::CreateScene(L"PlayeScene", new CPlayeScene); //씬은 씬매니저가 생성하게하자

		CSceneManager::LoadScene(L"PlayeScene");
	}

}