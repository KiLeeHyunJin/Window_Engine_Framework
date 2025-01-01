#pragma once
#include "CommonInclude.h"
#include "CScene.h"

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

		template<typename T>
		static CScene* CreateScene(const wstring& name)
		{
			T* createScene = new T();
			CScene* scene = static_cast<CScene*>(scene);
			scene->SetName(name);
			m_mapScene.insert(make_pair(name, scene));
			return scene;
		}

	private:
		static map<wstring, CScene*> m_mapScene;
		static CScene* m_pCurrentScene;
	};
	
#define SCENE CSceneManager
}

