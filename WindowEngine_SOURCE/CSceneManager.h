#pragma once
#include "CommonInclude.h"
#include "CScene.h"

namespace Framework
{
	class CApplication;

	class CRenderManager;
	class CCollisionManager;
	class CEventManager;
	class CScene;

	class CSceneManager
	{
	public:
		CSceneManager();
		virtual ~CSceneManager();

		static void InitMapDataSize(UINT size) 
		{ 
			m_vecScenes.resize(size); 
			m_vecScenes[m_vecScenes.size() - 1] = m_pDontDestroyScene;
		}

		template<typename T>
		static CScene* CreateScene(const std::wstring& name, const UINT idx )//씬은 씬매니저가 생성하게하자
		{
			CScene* pScene = FindScene(idx);
			if (pScene != nullptr)
			{	return pScene;	}

			T* createScene = new T();
			pScene = static_cast<CScene*>(createScene);

			m_pCurrentScene = pScene;
			pScene->SetName(name);
			pScene->SceneInitialize();

			if (m_vecScenes[idx] == nullptr)
			{
				m_vecScenes[idx] = pScene;
			}
			else
			{
				static_assert(true, L"There is already a stored data");
			}
			//m_mapScene.insert(make_pair(name, pScene));
			return pScene;
		}

		static CScene* LoadScene(const UINT idx);

		inline static CScene* GetCurrentScene()		{ return m_pCurrentScene; }
		inline static CScene* GetDontDestoryScene() { return m_pDontDestroyScene; }

		//static std::vector<CGameObject*> GetGameObject(Enums::eLayerType layer);

		friend CApplication;
		friend CRenderManager;
		friend CCollisionManager;
		friend CEventManager;
	private:
		static void Initialize();
		static void Release();

		static void Tick();
		static void LastTick();

		static void Destroy();
		static void Render(HDC hDC);

		static CScene* FindScene(const UINT idx);

		static const std::vector<CGameObject*>& GetDontDestroyGameObject(Enums::eLayerType layer);
		static const std::vector<CGameObject*>& GetGameObject(Enums::eLayerType layer);

		static std::vector<CScene*> m_vecScenes;
		static CScene* m_pCurrentScene;
		static CScene* m_pDontDestroyScene;
		static CScene* m_pChangeScene;
	};

	using SCENE = CSceneManager;
//#define SCENE CSceneManager
}

