#pragma once
#include "CommonInclude.h"



namespace Framework
{

	class GameObject;

	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void Initialize(HWND hWnd);
		void Tick();
		void LastTick();
		void Render();

	private:

		HWND m_hWnd;
		HDC m_hDC;

		GameObject* m_pGameObject;
	};

}

