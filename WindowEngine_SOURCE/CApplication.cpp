#include "CApplication.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CRenderManager.h"
#include "CResourceManager.h"
#include "CCollisionManager.h"
#include "CUIManager.h"
#include "CEventManager.h"

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
		EVENT::Initialize();
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
		EVENT::Release();

		RENDER::Release();
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

		EVENT::Tick();
		UI::Tick();

		COLLISION::Tick();
	}

	void CApplication::LastTick()
	{
		SCENE::LastTick();

		EVENT::LastTick();
		UI::LastTick();
	}

	void CApplication::Render()
	{
		RENDER::Render();
	}

	//void CApplication::Destroy()
	//{
	//	SCENE::Destroy();
	//}

	void CApplication::ChangeScreenSize(bool maximumScale)
	{
		RENDER::ChangeScreenSize(maximumScale);
	}

}






































