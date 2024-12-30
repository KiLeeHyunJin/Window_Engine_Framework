#include "Application.h"
#include "GameObject.h"


namespace Framework
{
	Application::Application() :
		m_hWnd(nullptr),
		m_hDC(nullptr),
		m_pGameObject(nullptr)
	{

	}
	Application::~Application()
	{

	}

	void Application::Initialize(HWND hWnd)
	{
		m_hWnd = hWnd;
		m_hDC = GetDC(m_hWnd);

		m_pGameObject = new GameObject();
	}

	void Application::Run()
	{
		Tick();
		LastTick();
		Render();
	}

	void Application::Tick()
	{
		float posX = m_pGameObject->GetPositionX();
		float posY = m_pGameObject->GetPositionY();
		if(GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			posX -= 0.01f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			posX += 0.01f;

		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			posY -= 0.01f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			posY += 0.01f;
		}
		m_pGameObject->SetPosition(posX , posY);

	}

	void Application::LastTick()
	{

	}

	void Application::Render()
	{
		HBRUSH bluBrush = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC,(HGDIOBJ)bluBrush);

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(m_hDC, (HGDIOBJ)redPen);
		SelectObject(m_hDC, oldPen);
		float posX = m_pGameObject->GetPositionX();
		float posY = m_pGameObject->GetPositionY();

		Rectangle(m_hDC, 50 - posX, 50 - posY, 50 + posX, 50 + posY);
		SelectObject(m_hDC, oldBrush);

		DeleteObject(bluBrush);
		DeleteObject(redPen);
	}

}






































