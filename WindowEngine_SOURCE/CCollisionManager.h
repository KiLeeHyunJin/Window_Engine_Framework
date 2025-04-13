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
			/// ��� �ݶ��̴����� ��Ƴ��� �ڷ���
			/// </summary>
			std::vector<CColliderComponent*> m_vecCollider		= {};
			bool* m_bArryCollision								= nullptr;
			UINT m_iCollTickComponentFPS						= 0;
			// CManagerBase��(��) ���� ��ӵ�
		};

	}

	
	using COLLISION = Manager::CCollisionManager;
}



