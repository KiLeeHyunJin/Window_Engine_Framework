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
		//class CRenderManager;
		//class CSceneManager;

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
			RELEASE_SINGLE(CCollisionManager)
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
			void Clear();
			void Render(HDC hdc) const;
			//void Render() override;


			friend CApplication;
		private:
			//CCollisionManager();
			virtual ~CCollisionManager();

			void Initialize();
			void Release();

			void Tick();
			void LastTick();



			__forceinline void InsertCollision();
			__forceinline void InsertActor(const std::vector<CActor*>& vecObjs);

			__forceinline void CollisionCircuit();

			__forceinline void CollisionStateUpdate(CColliderComponent* leftCollider, CColliderComponent* rightCollider);
			__forceinline bool GetLayerState(UINT left, UINT right);

			//std::unordered_map<UINT64, bool> m_unmapCollisions = {};
			std::unordered_map<UINT64, bool> collisionsA		= {};
			std::unordered_map<UINT64, bool> collisionsB		= {};

			std::unordered_map<UINT64, bool>* curr				= nullptr;
			std::unordered_map<UINT64, bool>* prev				= nullptr;

			//bool m_check = false;
			/// <summary>
			/// 모든 콜라이더들을 담아놓는 자료형
			/// </summary>
			std::vector<CColliderComponent*> m_vecCollider		= {};
			bool* m_bArryCollision								= nullptr;
			UINT m_iCollTickComponentFPS						= 0;
			// CManagerBase을(를) 통해 상속됨
		};

	}

	
	using COLLISION = Manager::CCollisionManager;
}



