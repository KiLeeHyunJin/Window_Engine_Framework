#include "CApplication.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CRenderManager.h"
#include "CResourceManager.h"

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
	}

	void CApplication::Release()
	{
		SCENE::Release();
		Resource::RESOURCE::Release();
		CRenderManager::Release();
	}

	void CApplication::Run()
	{
		Tick();
		LastTick();
		Render();
	}

	void CApplication::Tick()
	{
		INPUT::Tick();
		TIME::Tick();
		SCENE::Tick();
	}

	void CApplication::LastTick()
	{
		SCENE::LastTick();
	}

	void CApplication::Render()
	{
		CRenderManager::Render();
	}

	void CApplication::ChangeScreenSize(bool maximumScale)
	{
		CRenderManager::ChangeScreenSize(maximumScale);
	}

}






































