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
#include "CSoundManager.h"

//#include "CRenderer.h"

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
		GET_SINGLE(SOUND).Initialize();
		GET_SINGLE(RENDER).Initialize(hWnd, width, height, xPos, yPos, winStyle, menu, screen);
		GET_SINGLE(INPUT).Initialize(hWnd);
		GET_SINGLE(TIME).Initialize();
		GET_SINGLE(RESOURCE).Initialize();

		GET_SINGLE(OBJECT).Initialize();
		GET_SINGLE(COLLISION).Initialize();

		GET_SINGLE(EVENT).Initialize();

		GET_SINGLE(UI).Initialize();
		GET_SINGLE(SCENE).Initialize();

	}

	void CApplication::Release()
	{
		//GET_SINGLE(DATA).DestroyInstance();
		GET_SINGLE(SCENE).DestroyInstance();
		GET_SINGLE(COLLISION).DestroyInstance();
		GET_SINGLE(EVENT).DestroyInstance();
		GET_SINGLE(OBJECT).DestroyInstance();

		GET_SINGLE(RENDER).DestroyInstance();
		GET_SINGLE(UI).DestroyInstance();

		GET_SINGLE(INPUT).DestroyInstance();
		GET_SINGLE(TIME).DestroyInstance();
		GET_SINGLE(SOUND).DestroyInstance();
		GET_SINGLE(RESOURCE).DestroyInstance();

	}

	void CApplication::Run()
	{
		static float lag			= 0.0f;
		static float FIXED_STEP		= 1.f / 80.f;

		GET_SINGLE(TIME).Tick();
		const float deltaTime = GET_SINGLE(TIME).ApplicationDeltaTime();	// 프레임 간 경과 시간 업데이트
		lag += deltaTime;													// 누적 시간에 더함

		while (lag >= FIXED_STEP)											// 고정 시간 간격으로 Tick 호출
		{
			Tick();															// 게임 로직
			LastTick();														
			lag -= FIXED_STEP;
		}

		GET_SINGLE(COLLISION).Tick();										// 렌더 직전 충돌 검사
		FixedTick();														// 물리 계산 후 실행되는 Tick 호출

		Render();															// 렌더 업데이트 
	}

	void CApplication::Tick()
	{
		GET_SINGLE(INPUT).Tick();

		GET_SINGLE(SCENE).Tick(); // 업데이트
		GET_SINGLE(OBJECT).Tick();

		GET_SINGLE(EVENT).Tick(); // 예약 실행 (삭제, 추가, 씬 전환, 레이어 변경)
		GET_SINGLE(UI).Tick();
		GET_SINGLE(SOUND).Tick();

	}

	void CApplication::LastTick()
	{
		GET_SINGLE(SCENE).LastTick();
		GET_SINGLE(OBJECT).LastTick();

		GET_SINGLE(EVENT).LastTick(); // 씬 전환
		//GET_SINGLE(UI).LastTick();
	}

	void CApplication::FixedTick()
	{
		GET_SINGLE(OBJECT).FixedTick();
	}

	void CApplication::Render()
	{
		GET_SINGLE(RENDER).Render();
	}

	void CApplication::ChangeScreenSize(bool maximumScale)
	{
		GET_SINGLE(RENDER).ChangeScreenSize(maximumScale);
	}

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






































