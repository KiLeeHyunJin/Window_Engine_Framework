#include "CApplication.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CSceneManager.h"
#include "CRenderManager.h"
#include "CResourceManager.h"
#include "CCollisionManager.h"
#include "CUIManager.h"
#include "CEventManager.h"
#include "CDataManager.h"
#include "CObjectManager.h"

#include "CRenderer.h"

namespace Framework
{

	CApplication::CApplication() : m_hwnc(), m_hdc()
	{	}

	CApplication::~CApplication()
	{	}

	void CApplication::Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen)
	{
		//m_bRelease = false;
		m_hwnc = hWnd;
		m_hdc = ::GetDC(m_hwnc);

		DATA::Initialize();
		RENDER::Initialize(hWnd, width, height, xPos, yPos, winStyle, menu, screen);

		INPUT::Initialize(hWnd);
		TIME::Initialize();
		UI::Initialize();
		SCENE::Initialize();
		COLLISION::Initialize();
		EVENT::Initialize();
		OBJECT::Initialize();
		INPUT::SetResolution(RENDER::GetResolution());
	}

	void CApplication::Release()
	{
		SCENE::Release();
		OBJECT::Initialize();

		Resource::RESOURCE::Release();
		UI::Release();
		COLLISION::Release();
		EVENT::Release();

		RENDER::Release();
		

	}

	void CApplication::Run()
	{
		TickComponent();
		LastTickComponent();
		Render();
	}

	void CApplication::TickComponent()
	{
		TIME::TickComponent();
		INPUT::TickComponent();

		SCENE::TickComponent(); // 업데이트
		OBJECT::TickComponent();

		EVENT::TickComponent(); // 예약 실행 (삭제, 추가, 씬 전환, 레이어 변경)
		UI::TickComponent();

		COLLISION::TickComponent(); // 1초에 80번 업데이트
	}

	void CApplication::LastTickComponent()
	{
		SCENE::LastTickComponent();
		OBJECT::LastTickComponent();

		EVENT::LastTickComponent(); // 씬 전환
		//UI::LastTickComponent();
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
		const Maths::Vector2& resolution = RENDER::GetResolution();
		CCameraComponent* cam = Renderer::CRenderer::GetMainCamera();
		if (cam != nullptr)
		{
			cam->SetResolution(resolution);
		}
		INPUT::SetResolution(RENDER::GetResolution());
	}

}






































