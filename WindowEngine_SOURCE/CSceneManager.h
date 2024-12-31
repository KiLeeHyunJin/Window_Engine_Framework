#pragma once
#include "CommonInclude.h"
namespace Framework
{
	class CApplication;
	class CScene;

	class CSceneManager
	{
	public:
		CSceneManager();
		virtual ~CSceneManager();

		static void Initialize();
		static void Tick();
		static void LastTick();
		static void Render(HDC hDC);
		static void Release();

	private:
		static vector<CScene*> m_vecScene;
		static CScene* m_pCurrentScene;
	};
	
#define SCENE CSceneManager
}

