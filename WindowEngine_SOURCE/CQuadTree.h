#pragma once
#include "CommonInclude.h"

namespace Framework
{
	using namespace Maths;

	class CQuadTreeManager;
	class CQuadTreeNode;
	class CColliderComponent;
	class CQuadTree
	{
	public:
		CQuadTree(Vector2 size, int maxDepth, float constantK);
		~CQuadTree();

		void Clear();
		void Insert(CColliderComponent* pCollider);
		std::list<CColliderComponent*> Query(CColliderComponent* queryItem);

		int GetMaxDepth() const { return m_iMaxDepth; }
		float GetConstantK() const { return m_fConstantK; }

		void SetMaxDepth(int depth)			{ m_iMaxDepth = depth; }
		void SetConstantK(float constantK)	{ m_fConstantK = constantK; }
		void Release();

	private:
		int GetTargetDepth(CColliderComponent* item);

		CQuadTreeNode* m_pRootNode;
		int m_iMaxDepth;
		float m_fConstantK;
	};
}


