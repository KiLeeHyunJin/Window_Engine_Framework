#pragma once

#include "..\\WindowEngine_SOURCE\\CSceneManager.h"
#include "..\\WindowEngine_SOURCE\\CEventManager.h"
#include "..\\WindowEngine_SOURCE\\CObjectManager.h"

#include "CPlayScene.h"
#include "CTitleScene.h"
#include "CDevScene.h"

#include "ContentEnums.h"

namespace Framework
{
	void CreateScenes()
	{
		GET_SINGLE(OBJECT).InitLayerSize((UINT)eLayer::Size);
		GET_SINGLE(SCENE).InitSceneSize((UINT)eMap::Size);

		GET_SINGLE(SCENE).CreateScene<CDevScene>(L"DevScene", (UINT)eMap::Dev);
		GET_SINGLE(SCENE).CreateScene<CTitleScene>(L"TitleScene", (UINT)eMap::Title);
		GET_SINGLE(SCENE).CreateScene<CPlayScene>(L"PlayScene",(UINT)eMap::Play);


	}


	void LoadScene()
	{
		CreateScenes();
		GET_SINGLE(EVENT).LoadScene((UINT)eMap::Title);
	}



}