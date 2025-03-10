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
		const std::vector<CColliderComponent*>& Query(CColliderComponent* queryItem);
		const std::vector<CColliderComponent*>& Query(const Maths::Vector2& center, const Maths::Vector2& size);

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

		//list에서 vector로 바꾸고 930프레임에서 1000프레임으로 상승
		/// <summary>
		/// 충돌 가능성이 있는 노드를 담아 놓는 자료형
		/// </summary>
		std::vector<CQuadTreeNode*> m_pPossibleNodes;
		/// <summary>
		/// 충돌중인 콜라이더를 담아서 반환하는 자료형
		/// </summary>
		std::vector<CColliderComponent*> m_pCollisions;
	};
}


