#pragma once
#include "CScene.h"
//#include "CLayer.h"
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	class CActor;

	namespace Manager
	{

		class CSceneManager 
		{
			DECLARE_SINGLE(CSceneManager)
			RELEASE_SINGLE(CSceneManager)
		public:

			template<typename T>
			CScene* CreateScene(const std::wstring& name, const UINT idx)//씬은 씬매니저가 생성하게하자
			{
				static_assert(std::is_base_of<CScene, T>::value, L"T Type is Not Scene");

				CScene* pScene = FindScene(idx);
				if (pScene != nullptr)
				{
					return pScene;
				}

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

			void InitSceneSize(UINT size);

			//__forceinline CScene* GetCurrentScene() { return m_pCurrentScene; }
			//__forceinline CScene* GetDontDestoryScene()	{ return m_pDontDestroyScene;	}
			__forceinline const UINT	 GetSceneSize() { return (UINT)m_vecScenes.size(); }
			//std::vector<CActor*> GetActor(Enums::eLayerType layer);
			void Render(HDC hDC);
			CScene* LoadScene(const UINT idx);


			friend CApplication;
			//friend CRenderManager;
			//friend CCollisionManager;
			//friend CEventManager;
		private:
			//CSceneManager();
			~CSceneManager();

			void Initialize();
			void Release();

			void Tick();
			void LastTick();


			CScene* FindScene(const UINT idx);

			CScene* m_pCurrentScene				= nullptr;
			bool** m_bArrCollisionState			= nullptr;

			std::vector<CScene*> m_vecScenes	= {};
			UINT m_uiLayerSize					= 0;
		};
	}

	using SCENE = Manager::CSceneManager;
//#define SCENE CSceneManager
}

