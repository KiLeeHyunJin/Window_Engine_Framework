#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	//class CRenderManager;
	class CScene;
	class CColliderComponent;
	class CSceneManager;

	union CollisionID
	{
		CollisionID(): left(0), right(0)
		{}
		CollisionID(UINT left, UINT right) : left(left), right(right)
		{}
		struct 
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};

	class CCollisionManager
	{
	public:
		static void SetCollisionLayerState(Enums::eLayerType left, Enums::eLayerType right, bool enable);

		friend CApplication;
		//friend CRenderManager;
		friend CSceneManager;
	private:
		CCollisionManager();
		virtual ~CCollisionManager();

		static void Initialize();
		static void Release();
		
		static void Tick();
		static void LastTick();

		//static void Render(HDC hdc);

		static void Clear() 
		{ 
			m_unmapCollisions.clear(); 
			m_bsCollisionCheck->reset(); 
		}

		static const bool Intersect(const CColliderComponent* left, const CColliderComponent* right);

		static void CollisionCheck(CScene* pScene, Enums::eLayerType left, Enums::eLayerType right);
		static void CollisionStateUpdate(CColliderComponent* leftCollider, CColliderComponent* rightCollider);

		static bool BoxCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right);
		static bool CircleCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right);

		static std::bitset<(UINT)Enums::eLayerType::Size> m_bsCollisionCheck[(UINT)Enums::eLayerType::Size];
		static std::unordered_map<UINT64, bool> m_unmapCollisions;

	};
#define COLLISION  CCollisionManager
}



