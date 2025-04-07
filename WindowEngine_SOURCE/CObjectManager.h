#pragma once
#include "CommonInclude.h"
#include "CLayer.h"

namespace Framework
{
	class CApplication;
	class CRenderManager;
	class CColliderManager;
	class CActor;

	class CObjectManager
	{
	public:
		template<typename T>
		static T* CreateObject()
		{
			static_assert(std::is_base_of<CActor, T>::value, "T is not from CComponent");

			T* object = new T();
			object->BeginPlay();
			return object;
		}

		static void AddActor(CActor* pActor);
		static bool EraseInLayer(CActor* pActor);
		static void Clear() { m_unObjects.clear(); }

		static CActor* GetActor(UINT32 actorId)
		{
			auto iter = m_unObjects.find(actorId);
			if (iter == m_unObjects.end())
			{
				return nullptr;
			}
			return iter->second;
		}
		__forceinline static const UINT	 GetLayerSize() { return m_uiLayerSize; }
		static void InitLayerSize(UINT layerSize);


		friend CApplication;
		friend CRenderManager;
		friend CColliderManager;
	private:
		CObjectManager();
		~CObjectManager();

		static void Initialize();


		static void Release();

		static void TickComponent();
		static void LastTickComponent();
		static void Render(HDC hdc);


		__forceinline static const std::vector<CActor*>& GetDontDestroyActors(UINT layer)
		{
			return m_vecDontDestoryLayer[layer]->GetActor();
		}

		__forceinline static const std::vector<CActor*>& GetActors(UINT layer)
		{
			return m_vecLayer[layer]->GetActor();
		}

		static UINT m_uiLayerSize;
		static std::unordered_map<UINT32, CActor*> m_unObjects;

		static std::vector<CLayer*> m_vecLayer;
		static std::vector<CLayer*> m_vecDontDestoryLayer;
	};
	using OBJECT = CObjectManager;

}

