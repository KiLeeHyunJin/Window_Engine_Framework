#pragma once
#include "CommonInclude.h"
#include "CScene.h"

namespace Framework
{
	class CApplication;
	class CRenderManager;
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

		inline static CScene* GetCurrentScene()		{ return m_pCurrentScene; }
		inline static CScene* GetDontDestoryScene() { return m_pDontDestroyScene; }

		friend CApplication;
		friend CRenderManager;
	private:
		static void Initialize();
		static void Release();

		static void Tick();
		static void LastTick();
		static void Destroy();
		static void Render(HDC hDC);

		static CScene* FindScene(const std::wstring& name);

		static std::map<std::wstring, CScene*> m_mapScene;
		static CScene* m_pCurrentScene;
		static CScene* m_pDontDestroyScene;
	};
	
#define SCENE CSceneManager
}

