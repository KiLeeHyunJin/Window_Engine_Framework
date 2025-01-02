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
		static CScene* CreateScene(const wstring& name )
		{
			T* createScene = new T();
			CScene* scene = static_cast<CScene*>(createScene);
			scene->SetName(name);
			scene->Initialize();
			m_mapScene.insert(make_pair(name, scene));
			return scene;
		}

		static CScene* LoadScene(const wstring& name)
		{
			map<wstring, CScene*>::iterator iter = m_mapScene.find(name);
			if (iter != m_mapScene.end())
			{
				m_pCurrentScene = iter->second;
				return m_pCurrentScene;
			}
			return nullptr;
		}

		friend CApplication;
	private:
		static void Initialize();
		static void Release();

		static void Tick();
		static void LastTick();

		static void Render(HDC hDC);

		static map<wstring, CScene*> m_mapScene;
		static CScene* m_pCurrentScene;
	};
	
#define SCENE CSceneManager
}

