#include "CApplication.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CRenderManager.h"
#include "CResourceManager.h"
#include "CCollisionManager.h"

#include "CRenderer.h"

namespace Framework
{
	CApplication::CApplication()
	{
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen)
	{
		CRenderManager::Initialize(hWnd, width, height, xPos, yPos, winStyle, menu, screen);

		INPUT::Initialize();
		TIME::Initialize();
		SCENE::Initialize();
		COLLISION::Initialize();
	}

	void CApplication::Release()
	{
		SCENE::Release();
		Resource::RESOURCE::Release();
		RENDER::Release();
		COLLISION::Release();
	}

	void CApplication::Run()
	{
		Tick();
		LastTick();
		Render();
		Destroy();
	}

	void CApplication::Tick()
	{
		INPUT::Tick();
		TIME::Tick();
		SCENE::Tick();
		COLLISION::Tick();
	}

	void CApplication::LastTick()
	{
		SCENE::LastTick();
	}

	void CApplication::Render()
	{
		RENDER::Render();
	}

	void CApplication::Destroy()
	{
		SCENE::Destroy();
	}

	void CApplication::ChangeScreenSize(bool maximumScale)
	{
		RENDER::ChangeScreenSize(maximumScale);
	}

}






































