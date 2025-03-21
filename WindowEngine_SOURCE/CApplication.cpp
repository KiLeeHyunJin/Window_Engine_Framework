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

		SCENE::Tick(); // 업데이트

		EVENT::Tick(); // 예약 실행 (삭제, 추가, 씬 전환, 레이어 변경)
		UI::Tick();

		COLLISION::Tick(); // 1초에 80번 업데이트
	}

	void CApplication::LastTick()
	{
		SCENE::LastTick();

		EVENT::LastTick(); // 씬 전환
		//UI::LastTick();
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






































