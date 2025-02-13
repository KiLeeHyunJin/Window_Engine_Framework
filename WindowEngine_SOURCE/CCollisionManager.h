#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	class CRenderManager;
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

		/// <summary>
		/// 이전 Tick의 기준에서 충돌체를 가져옴
		/// </summary>
		static const std::list<CColliderComponent*>& GetCollisionCollider(const Maths::Vector2& center,const Maths::Vector2& size);

		/// <summary>
		/// 이전 Tick의 기준에서 충돌체를 가져옴
		/// </summary>
		static const std::list<CColliderComponent*>& GetCollisionCollider(const Rect& rect);

		/// <summary>
		/// 사용은 가능하나 최적화가 필요
		/// </summary>
		static bool Raycast(const Ray& ray, CColliderComponent& hitObject, const std::vector<CColliderComponent*>& ignores);
		static bool Raycast(const Ray& ray, CColliderComponent& hitObject, const std::vector<Enums::eLayerType>& checkLayer);


		friend CApplication;
		friend CRenderManager;
		friend CSceneManager;
	private:
		CCollisionManager();
		virtual ~CCollisionManager();

		static void Initialize();
		static void Release();
		
		static void Tick();
		static void LastTick();

		static void Render(HDC hdc);

		static void Clear();

		//static bool Raycast(Ray& ray, CColliderComponent& hitObject);

		static const bool Intersect(const CColliderComponent* left, const CColliderComponent* right);

		static void InsertCollision(std::list<CColliderComponent*>& listCollider);
		static void CollisionCircuit(const std::list<CColliderComponent*>& listCollider);

		static void CollisionCheck(CScene* pScene, Enums::eLayerType left, Enums::eLayerType right);
		static void CollisionStateUpdate(CColliderComponent* leftCollider, CColliderComponent* rightCollider);

		static bool BoxCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right);
		static bool CircleCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right);

		static std::bitset<(UINT)Enums::eLayerType::Size> m_bsCollisionCheck[(UINT)Enums::eLayerType::Size];
		static std::unordered_map<UINT64, bool> m_unmapCollisions;

	};
#define COLLISION  CCollisionManager
}



