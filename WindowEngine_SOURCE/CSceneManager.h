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
		static CScene* CreateScene(const std::wstring& name )//씬은 씬매니저가 생성하게하자
		{
			CScene* pScene = nullptr;//FindScene(name);
			//if (scene != nullptr)
			//{
			//	return scene;
			//}
			T* createScene = new T();
			pScene = static_cast<CScene*>(createScene);
			m_pCurrentScene = pScene;
			m_pCurrentScene->SetName(name);
			m_pCurrentScene->Initialize();
			m_mapScene.insert(make_pair(name, pScene));
			return pScene;
		}

		static CScene* LoadScene(const std::wstring& name);

		inline static CScene* GetCurrentScene()		{ return m_pCurrentScene; }
		inline static CScene* GetDontDestoryScene() { return m_pDontDestroyScene; }
		static std::vector<CGameObject*> GetGameObject(Enums::eLayerType layer);


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
	using SCENE = CSceneManager;
//#define SCENE CSceneManager
}

