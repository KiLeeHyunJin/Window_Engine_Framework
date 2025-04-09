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
			/// 해당 위치를 중심으로 size크기와 충돌한 객체를 가져온다.
			/// </summary>
			const std::vector<CColliderComponent*>& GetCollisionCollider(const Maths::Vector2& center, const Maths::Vector2& size);

			/// <summary>
			/// 해당 Rect와 충돌한 객체를 가져온다.
			/// </summary>
			const std::vector<CColliderComponent*>& GetCollisionCollider(const Rect& rect);

			/// <summary>
			/// 무시 목록에 존재하지 않은 방향의 근거리 객체를 가져온다.
			/// </summary>
			bool Raycast(const Ray& ray, CColliderComponent*& hitObject, std::vector<CColliderComponent*>& ignores);


			/// <summary>
			/// 특정 레이어의 객체만 체크하여 가져온다.
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
			/// 모든 콜라이더들을 담아놓는 자료형
			/// </summary>
			std::vector<CColliderComponent*> m_vecCollider		= {};
			bool* m_bArryCollision								= nullptr;
			INT m_iCollTickComponentFPS							= 0;
		};

	}

	
	using COLLISION = Manager::CCollisionManager;
}



