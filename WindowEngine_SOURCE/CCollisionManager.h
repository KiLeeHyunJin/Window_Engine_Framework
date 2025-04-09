#pragma once
#include "CommonInclude.h"


namespace Framework
{
	class CApplication;

	class CScene;
	class CColliderComponent;
	
	class CActor;

	namespace Manager
	{
		class CRenderManager;
		class CSceneManager;

		union CollisionID
		{
			CollisionID() : left(0), right(0)
			{
			}
			CollisionID(UINT left, UINT right) : left(left), right(right)
			{
			}
			struct
			{
				UINT32 left, right;
			};
			UINT64 id;
		};

		class CCollisionManager
		{
			DECLARE_SINGLE(CCollisionManager)
			RELEASE_SINGLE
		public:
			void SetCollisionLayerState(UINT left, UINT right, bool enable);
			void InitCollisionLayer();

			/// <summary>
			/// �ش� ��ġ�� �߽����� sizeũ��� �浹�� ��ü�� �����´�.
			/// </summary>
			const std::vector<CColliderComponent*>& GetCollisionCollider(const Maths::Vector2& center, const Maths::Vector2& size);

			/// <summary>
			/// �ش� Rect�� �浹�� ��ü�� �����´�.
			/// </summary>
			const std::vector<CColliderComponent*>& GetCollisionCollider(const Rect& rect);

			/// <summary>
			/// ���� ��Ͽ� �������� ���� ������ �ٰŸ� ��ü�� �����´�.
			/// </summary>
			bool Raycast(const Ray& ray, CColliderComponent*& hitObject, std::vector<CColliderComponent*>& ignores);


			/// <summary>
			/// Ư�� ���̾��� ��ü�� üũ�Ͽ� �����´�.
			/// </summary>
			bool Raycast(const Ray& ray, CColliderComponent*& hitObject, const std::vector<UINT>& checkLayer);


			friend CApplication;
			friend CRenderManager;
			friend CSceneManager;
		private:
			//CCollisionManager();
			virtual ~CCollisionManager();

			void Initialize();
			void Release();

			void Tick();
			void LastTick();

			void Render(HDC hdc);

			void Clear();

			//bool Raycast(Ray& ray, CColliderComponent& hitObject);

			//__forceinline const bool Intersect(const CColliderComponent* left, const CColliderComponent* right);


			__forceinline void InsertCollision();
			__forceinline void InsertActor(const std::vector<CActor*>& vecObjs);

			__forceinline void CollisionCircuit();

			//void CollisionCheck(CScene* pScene, Enums::eLayerType left, Enums::eLayerType right);
			//void CollisionCheck(const std::vector<CActor*>& lefts, const std::vector<CActor*>& rights);

			__forceinline void CollisionStateUpdate(CColliderComponent* leftCollider, CColliderComponent* rightCollider);

			//__forceinline bool BoxCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right);
			//__forceinline bool CircleCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right);

			__forceinline bool GetLayerState(UINT left, UINT right);

			//std::vector<std::vector<bool>> m_vectorCollisionCheck;
			//std::bitset<(UINT)Enums::eLayerType::Size> m_bsCollisionCheck[(UINT)Enums::eLayerType::Size];
			std::unordered_map<UINT64, bool> m_unmapCollisions = {};
			/// <summary>
			/// ��� �ݶ��̴����� ��Ƴ��� �ڷ���
			/// </summary>
			std::vector<CColliderComponent*> m_vecCollider		= {};
			bool* m_bArryCollision								= nullptr;
			INT m_iCollTickComponentFPS							= 0;
		};

	}

	
	using COLLISION = Manager::CCollisionManager;
}



