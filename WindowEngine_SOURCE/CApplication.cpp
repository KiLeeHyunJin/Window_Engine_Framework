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

		//GET_SINGLE(DATA).Initialize();
		GET_SINGLE(RENDER).Initialize(hWnd, width, height, xPos, yPos, winStyle, menu, screen);
		GET_SINGLE(INPUT).Initialize(hWnd);
		GET_SINGLE(INPUT).Initialize(hWnd);
		GET_SINGLE(TIME).Initialize();
		GET_SINGLE(UI).Initialize();
		GET_SINGLE(SCENE).Initialize();
		GET_SINGLE(COLLISION).Initialize();
		GET_SINGLE(EVENT).Initialize();
		GET_SINGLE(OBJECT).Initialize();
		GET_SINGLE(RESOURCE).Initialize();

		//GET_SINGLE(INPUT).SetResolution(GET_SINGLE(RENDER).GetResolution());
	}

	void CApplication::Release()
	{

		//GET_SINGLE(DATA).DestroyInstance();


		GET_SINGLE(SCENE).DestroyInstance();
		GET_SINGLE(COLLISION).DestroyInstance();
		GET_SINGLE(EVENT).DestroyInstance();
		GET_SINGLE(OBJECT).DestroyInstance();

		GET_SINGLE(UI).DestroyInstance();

		GET_SINGLE(RENDER).DestroyInstance();
		GET_SINGLE(RESOURCE).DestroyInstance();
		
		GET_SINGLE(INPUT).DestroyInstance();
		GET_SINGLE(TIME).DestroyInstance();
	}

	void CApplication::Run()
	{
		Tick();
		LastTick();
		Render();
	}

	void CApplication::Tick()
	{
		GET_SINGLE(TIME).Tick();
		GET_SINGLE(INPUT).Tick();

		GET_SINGLE(SCENE).Tick(); // ������Ʈ
		GET_SINGLE(OBJECT).Tick();

		GET_SINGLE(EVENT).Tick(); // ���� ���� (����, �߰�, �� ��ȯ, ���̾� ����)
		GET_SINGLE(UI).Tick();

		GET_SINGLE(COLLISION).Tick(); // 1�ʿ� 80�� ������Ʈ
	}

	void CApplication::LastTick()
	{
		GET_SINGLE(SCENE).LastTick();
		GET_SINGLE(OBJECT).LastTick();

		GET_SINGLE(EVENT).LastTick(); // �� ��ȯ
		//GET_SINGLE(UI).LastTick();
	}

	void CApplication::Render()
	{
		GET_SINGLE(RENDER).Render();
	}

	//void CApplication::Destroy()
	//{
	//	GET_SINGLE(SCENE).Destroy();
	//}

	void CApplication::ChangeScreenSize(bool maximumScale)
	{
		GET_SINGLE(RENDER).ChangeScreenSize(maximumScale);

		//CCameraComponent* cam = Renderer::CRenderer::GetMainCamera();
		//if (cam != nullptr)
		//{
		//	const Maths::Vector2& resolution = GET_SINGLE(RENDER).GetResolution();
		//	cam->SetResolution(resolution);
		//}
		//GET_SINGLE(INPUT).SetResolution(resolution);
	}

	//const Maths::Vector2& GetResolution()
	//{
	//	return GET_SINGLE(RENDER).GetResolution();
	//}

	HDC CApplication::GetHDC() const
	{
		return GET_SINGLE(RENDER).GetHDC();
	}
	bool CApplication::GetScreenState() const
	{
		return GET_SINGLE(RENDER).m_bScreenState;
	}
	HWND CApplication::GetHWND() const
	{
		return GET_SINGLE(RENDER).m_hWnd;
	}

}






































