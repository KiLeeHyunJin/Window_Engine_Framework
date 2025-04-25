#include "CScene.h"

#include "CLayer.h"
#include "CActor.h"

//#include "CInputManager.h"
//#include "CCollisionManager.h"
//#include "CActor.h"

namespace Framework
{
	CScene::CScene()
	{
	}

	CScene::~CScene()
	{
	}

	void CScene::SceneInitialize()
	{
		Initialize();
	}

	void CScene::SceneRelease()
	{
		Release();
	}

	void CScene::SceneTick()
	{
		Tick();

	}

	void CScene::SceneLastTick()
	{
		LastTick();
	}


	void CScene::SceneRender(HDC hdc)
	{
		Render(hdc);

	}
	
}