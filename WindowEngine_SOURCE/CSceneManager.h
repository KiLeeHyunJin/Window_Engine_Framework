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

		template<typename T>
		static CScene* CreateScene(const std::wstring& name )
		{
			T* createScene = new T();
			CScene* scene = static_cast<CScene*>(createScene);
			m_pCurrentScene = scene;
			scene->SetName(name);
			scene->Initialize();
			m_mapScene.insert(make_pair(name, scene));
			return scene;
		}

		static CScene* LoadScene(const std::wstring& name);
		static CScene* GetCurrentScene() { return m_pCurrentScene; }
		friend CApplication;
	private:
		static void Initialize();
		static void Release();

		static void Tick();
		static void LastTick();

		static void Render(HDC hDC);

		static std::map<std::wstring, CScene*> m_mapScene;
		static CScene* m_pCurrentScene;
	};
	
#define SCENE CSceneManager
}

