#pragma once
#include "CLayer.h"
#include "CEventManager.h"
#include "CommonInclude.h"
namespace Framework
{
	class CApplication;
	//class CRenderManager;
	//class CCollisionManager;
	//class CSceneManager;
	//class CActor;

	namespace Manager
	{
		class CObjectManager 
		{
			DECLARE_SINGLE(CObjectManager)
			RELEASE_SINGLE(CObjectManager)
		public:
			template<typename T>
			T* CreateObject(UINT layer, bool dontDestroy = false)
			{
				static_assert(std::is_base_of<CActor, T>::value, "T is not from CComponent");

				T* object = new T(layer);
				GET_SINGLE(EVENT).AddActor(object, dontDestroy);
				return object;
			}

			__forceinline CActor* GetActor(UINT32 actorId)
			{
				auto iter = m_unObjects.find(actorId);
				return iter == m_unObjects.end() ? nullptr : iter->second;
			}

			__forceinline const UINT GetLayerSize() const { return m_uiLayerSize; }

			void InitLayerSize(UINT layerSize);

			__forceinline const std::vector<CActor*>& GetDontDestroyActors(UINT layer)	//CollisionManager
			{
				return m_vecDontDestoryLayer[layer]->GetActor();
			}

			__forceinline const std::vector<CActor*>& GetActors(UINT layer)				//CollisionManager	
			{
				return m_vecLayer[layer]->GetActor();
			}
			void Render(HDC hdc);								//RenderManager
			void AddActorID(CActor* pActor);						//EventManager
			void AddActor(CActor* pActor);						//EventManager

			void AddInLayer(CActor* pActor);						//EventManager
			bool EraseInLayer(CActor* pActor);					//EventManager

			void Clear(bool allClear = false);					//SceneManager
			void Destroy();										//CollisionManager

			__forceinline void RemoveActor(UINT32 actorId) 		//EventManager
			{
				auto iter = m_unObjects.find(actorId);
				if (iter != m_unObjects.end())
				{
					m_unObjects.erase(actorId);
				}
			}


			friend CApplication;		//�Ź� �Լ� ������ ���� ���
			//friend CRenderManager;		//������ ���� ���
			//friend CCollisionManager;	//�浹�� ���� ������Ʈ ������������ ���
			//friend CEventManager;		//���̾� ���� �� ������Ʈ �߰� ������ ���� ���
			//friend CSceneManager;		//�� ��ȯ�Ҷ����� ������Ʈ ������ ���� ���
		private:
			//CObjectManager();
			~CObjectManager();

			void Initialize();									//Application
			void Release();										//Application

			void Tick();											//Application
			void LastTick();										//Application

			UINT m_uiLayerSize								= 0;
			std::unordered_map<UINT32, CActor*> m_unObjects = {};

			std::vector<CLayer*> m_vecLayer					= {};
			std::vector<CLayer*> m_vecDontDestoryLayer		= {};
		};
	}

	
	using OBJECT = Manager::CObjectManager;

}

