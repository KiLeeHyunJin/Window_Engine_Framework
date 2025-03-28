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

	CApplication::CApplication() : m_hwnc(), m_hdc()
	{	}

	CApplication::~CApplication()
	{	}

	void CApplication::Initialize(HWND hWnd, int  width, int height, int xPos, int yPos, DWORD winStyle, bool menu, bool screen)
	{
		//m_bRelease = false;
		m_hwnc = hWnd;
		m_hdc = ::GetDC(m_hwnc);

		RENDER::Initialize(hWnd, width, height, xPos, yPos, winStyle, menu, screen);

		INPUT::Initialize(hWnd);
		TIME::Initialize();
		UI::Initialize();
		SCENE::Initialize();
		COLLISION::Initialize();
		EVENT::Initialize();

		INPUT::SetResolution(RENDER::GetResolution());
	}

	void CApplication::Release()
	{
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
		TIME::Tick();
		INPUT::Tick();

		SCENE::Tick(); // ������Ʈ

		EVENT::Tick(); // ���� ���� (����, �߰�, �� ��ȯ, ���̾� ����)
		UI::Tick();

		COLLISION::Tick(); // 1�ʿ� 80�� ������Ʈ
	}

	void CApplication::LastTick()
	{
		SCENE::LastTick();

		EVENT::LastTick(); // �� ��ȯ
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
		const Maths::Vector2& resolution = RENDER::GetResolution();
		CCameraComponent* cam = Renderer::CRenderer::GetMainCamera();
		if (cam != nullptr)
		{
			cam->SetResolution(resolution);
		}
		INPUT::SetResolution(RENDER::GetResolution());
	}

}






































