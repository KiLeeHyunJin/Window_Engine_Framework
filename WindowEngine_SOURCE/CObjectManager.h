#pragma once
#include "CommonInclude.h"
#include "CLayer.h"
#include "CEventManager.h"

namespace Framework
{
	class CApplication;
	class CRenderManager;
	class CCollisionManager;
	class CSceneManager;
	class CActor;

	namespace Manager
	{
		class CObjectManager
		{
		public:
			template<typename T>
			static T* CreateObject(UINT layer, bool dontDestroy = false)
			{
				static_assert(std::is_base_of<CActor, T>::value, "T is not from CComponent");

				T* object = new T(layer);
				EVENT::AddActor(object, dontDestroy);
				return object;
			}

			__forceinline static CActor* GetActor(UINT32 actorId)
			{
				auto iter = m_unObjects.find(actorId);
				return iter == m_unObjects.end() ? nullptr : iter->second;
			}

			__forceinline static const UINT	 GetLayerSize() { return m_uiLayerSize; }

			static void InitLayerSize(UINT layerSize);


			friend CApplication;		//�Ź� �Լ� ������ ���� ���
			friend CRenderManager;		//������ ���� ���
			friend CCollisionManager;	//�浹�� ���� ������Ʈ ������������ ���
			friend CEventManager;		//���̾� ���� �� ������Ʈ �߰� ������ ���� ���
			friend CSceneManager;		//�� ��ȯ�Ҷ����� ������Ʈ ������ ���� ���
		private:
			CObjectManager();
			~CObjectManager();

			static void Initialize();									//Application
			static void Release();										//Application

			static void Tick();											//Application
			static void LastTick();										//Application

			static void Render(HDC hdc);								//RenderManager

			static void Clear(bool allClear = false);					//SceneManager

			static void AddActorID(CActor* pActor);						//EventManager
			static void AddActor(CActor* pActor);						//EventManager

			static void AddInLayer(CActor* pActor);						//EventManager
			static bool EraseInLayer(CActor* pActor);					//EventManager

			static void Destroy();										//CollisionManager

			__forceinline static void RemoveActor(UINT32 actorId) 		//EventManager
			{
				auto iter = m_unObjects.find(actorId);
				if (iter != m_unObjects.end())
				{
					m_unObjects.erase(actorId);
				}
			}

			__forceinline static const std::vector<CActor*>& GetDontDestroyActors(UINT layer)	//CollisionManager
			{
				return m_vecDontDestoryLayer[layer]->GetActor();
			}

			__forceinline static const std::vector<CActor*>& GetActors(UINT layer)				//CollisionManager	
			{
				return m_vecLayer[layer]->GetActor();
			}

			static UINT m_uiLayerSize;
			static std::unordered_map<UINT32, CActor*> m_unObjects;

			static std::vector<CLayer*> m_vecLayer;
			static std::vector<CLayer*> m_vecDontDestoryLayer;
		};
	}

	
	using OBJECT = Manager::CObjectManager;

}

