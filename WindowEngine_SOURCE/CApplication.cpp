#include "CApplication.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CRenderManager.h"
#include "CResourceManager.h"
#include "CCollisionManager.h"
#include "CUIManager.h"

#include "CRenderer.h"

namespace Framework
{
	CApplication::CApplication() : m_bRelease(true)
	{
	}

	CApplication::~CApplication()
	{
	}

	void CApplication::Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen)
	{
		m_bRelease = false;
		RENDER::Initialize(hWnd, width, height, xPos, yPos, winStyle, menu, screen);

		INPUT::Initialize();
		TIME::Initialize();
		UI::Initialize();
		SCENE::Initialize();
		COLLISION::Initialize();
	}

	void CApplication::Release()
	{
		//if (m_bRelease)
		//{	return;	}
		//m_bRelease = true;

		SCENE::Release();
		Resource::RESOURCE::Release();
		UI::Release();
		COLLISION::Release();

		RENDER::Release();
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
		UI::Tick();
		COLLISION::Tick();
		SCENE::Tick();
	}

	void CApplication::LastTick()
	{
		UI::LastTick();
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






































