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
		/// �ش� ��ġ�� �߽����� sizeũ��� �浹�� ��ü�� �����´�.
		/// </summary>
		static const std::vector<CColliderComponent*>& GetCollisionCollider(const Maths::Vector2& center,const Maths::Vector2& size);

		/// <summary>
		/// �ش� Rect�� �浹�� ��ü�� �����´�.
		/// </summary>
		static const std::vector<CColliderComponent*>& GetCollisionCollider(const Rect& rect);

		/// <summary>
		/// ���� ��Ͽ� �������� ���� ������ �ٰŸ� ��ü�� �����´�.
		/// </summary>
		static bool Raycast(const Ray& ray, CColliderComponent*& hitObject, std::vector<CColliderComponent*>& ignores);


		/// <summary>
		/// Ư�� ���̾��� ��ü�� üũ�Ͽ� �����´�.
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
		/// ��� �ݶ��̴����� ��Ƴ��� �ڷ���
		/// </summary>
		static std::vector<CColliderComponent*> m_vecCollider;
		static bool* m_bArryCollision;

	};
	using COLLISION = CCollisionManager;
}



