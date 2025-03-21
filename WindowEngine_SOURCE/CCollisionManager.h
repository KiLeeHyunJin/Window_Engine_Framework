#pragma once
#include "CommonInclude.h"


namespace Framework
{
	class CApplication;
	class CRenderManager;
	class CScene;
	class CColliderComponent;
	class CSceneManager;
	class CGameObject;

	union CollisionID
	{
		CollisionID(): left(0), right(0)
		{}
		CollisionID(UINT left, UINT right) : left(left), right(right)
		{}
		struct 
		{
			UINT32 left, right;
		};
		UINT64 id;
	};

	class CCollisionManager
	{
	public:
		static void SetCollisionLayerState(UINT left, UINT right, bool enable);

		/// <summary>
		/// 해당 위치를 중심으로 size크기와 충돌한 객체를 가져온다.
		/// </summary>
		static const std::vector<CColliderComponent*>& GetCollisionCollider(const Maths::Vector2& center,const Maths::Vector2& size);

		/// <summary>
		/// 해당 Rect와 충돌한 객체를 가져온다.
		/// </summary>
		static const std::vector<CColliderComponent*>& GetCollisionCollider(const Rect& rect);

		/// <summary>
		/// 무시 목록에 존재하지 않은 방향의 근거리 객체를 가져온다.
		/// </summary>
		static bool Raycast(const Ray& ray, CColliderComponent*& hitObject, std::vector<CColliderComponent*>& ignores);


		/// <summary>
		/// 특정 레이어의 객체만 체크하여 가져온다.
		/// </summary>
		static bool Raycast(const Ray& ray, CColliderComponent*& hitObject, const std::vector<UINT>& checkLayer);


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

		static void InitCollisionLayer();

		static void ClearGameObject();
		//static bool Raycast(Ray& ray, CColliderComponent& hitObject);

		__forceinline static const bool Intersect(const CColliderComponent* left, const CColliderComponent* right);
	

		__forceinline static void InsertCollision();
		__forceinline static void InsertGameObject(CColliderComponent* pCollider);

		__forceinline static void CollisionCircuit();

		//static void CollisionCheck(CScene* pScene, Enums::eLayerType left, Enums::eLayerType right);
		//static void CollisionCheck(const std::vector<CGameObject*>& lefts, const std::vector<CGameObject*>& rights);

		__forceinline static void CollisionStateUpdate(CColliderComponent* leftCollider, CColliderComponent* rightCollider);

		__forceinline static bool BoxCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right);
		__forceinline static bool CircleCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right);

		__forceinline static bool GetLayerState(UINT left, UINT right);

		//static std::vector<std::vector<bool>> m_vectorCollisionCheck;
		//static std::bitset<(UINT)Enums::eLayerType::Size> m_bsCollisionCheck[(UINT)Enums::eLayerType::Size];
		static std::unordered_map<UINT64, bool> m_unmapCollisions;
		/// <summary>
		/// 모든 콜라이더들을 담아놓는 자료형
		/// </summary>
		static std::vector<CColliderComponent*> m_vecCollider;
		static bool* m_bArryCollision;

	};
	using COLLISION = CCollisionManager;
}



