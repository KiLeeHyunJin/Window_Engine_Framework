#pragma once
#include "CommonInclude.h"
namespace Framework
{
	class CCollisionManager;
	class CColliderComponent;
	class CQuadTree;

	class CQuadTreeManager
	{
	public:



		friend CCollisionManager;
	private:
		CQuadTreeManager();
		~CQuadTreeManager();

		static void Initialize(Maths::Vector2 size, int maxDepth, float constrantK);
		static void Insert(CColliderComponent* pCollider);
		static std::list<CColliderComponent*> Query(CColliderComponent* queryItem);
		static void Clear();
		static void Release();
		static CQuadTree* m_pQuadTree;
	};

}

