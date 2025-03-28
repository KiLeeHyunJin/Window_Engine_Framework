#pragma once
#include "CommonInclude.h"
#include "CScene.h"
#include "CLayer.h"

namespace Framework
{
	class CApplication;

	class CRenderManager;
	class CCollisionManager;
	class CEventManager;
	class CGameObject;

	class CSceneManager
	{
	public:


		template<typename T>
		static CScene* CreateScene(const std::wstring& name, const UINT idx )//씬은 씬매니저가 생성하게하자
		{
			static_assert(std::is_base_of<CScene, T>::value, L"T Type is Not Scene");

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

		static void InitDataSize(UINT size, UINT layerSize);

		__forceinline static CScene* GetCurrentScene()		{ return m_pCurrentScene;		}
		__forceinline static CScene* GetDontDestoryScene()	{ return m_pDontDestroyScene;	}
		__forceinline static const UINT	 GetLayerSize()		{ return m_uiLayerSize;		}
		//static std::vector<CGameObject*> GetGameObject(Enums::eLayerType layer);

		friend CApplication;
		friend CRenderManager;
		friend CCollisionManager;
		friend CEventManager;
	private:
		CSceneManager();
		~CSceneManager();

		static void Initialize();
		static void Release();

		static void Tick();
		static void LastTick();

		static void Destroy();
		static void Render(HDC hDC);

		static void InitDontDestroyScene();

		static CScene* LoadScene(const UINT idx);
		static CScene* FindScene(const UINT idx);


		__forceinline static const std::vector<CGameObject*>& GetDontDestroyGameObject(UINT layer)
		{		return m_pDontDestroyScene->GetLayer(layer)->GetGameObject();		}

		__forceinline static const std::vector<CGameObject*>& GetGameObject(UINT layer)
		{		return  m_pCurrentScene->GetLayer(layer)->GetGameObject();			}

		static bool** m_bArrCollisionState;

		static std::vector<CScene*> m_vecScenes;
		static UINT m_uiLayerSize;

		static CScene* m_pCurrentScene;
		static CScene* m_pDontDestroyScene;

		//static CScene* m_pChangeScene;
	};

	using SCENE = CSceneManager;
//#define SCENE CSceneManager
}

