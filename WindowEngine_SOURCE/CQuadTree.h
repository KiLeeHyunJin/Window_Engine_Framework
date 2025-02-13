#pragma once
#include "CommonInclude.h"
#include "CQuadTreeManager.h"

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
		const std::list<CColliderComponent*>& Query(CColliderComponent* queryItem);
		const std::list<CColliderComponent*>& Query(const Maths::Vector2& center, const Maths::Vector2& size);

		bool Raycast(const Ray& ray, float& closestHit, CColliderComponent& hitObject, const std::vector<CColliderComponent*>& removes);
		bool Raycast(const Ray& ray, float& closestHit, CColliderComponent& hitObject, const std::vector<Enums::eLayerType>& checkLayer);

		void Render(HDC hdc);
		int GetMaxDepth() const { return m_iMaxDepth; }
		float GetConstantK() const { return m_fConstantK; }

		//void SetMaxDepth(int depth)			{ m_iMaxDepth = depth; }
		void SetConstantK(float constantK)	{ m_fConstantK = constantK; }
		void Release();

	private:
		int GetTargetDepth(CColliderComponent* item);
		CQuadTreeNode* m_pRootNode;
		const int m_iMaxDepth;
		float m_fConstantK;
		std::list<CQuadTreeNode*> m_pPossibleNodes;
		std::list<CColliderComponent*> m_pCollisionList;
	};
}


