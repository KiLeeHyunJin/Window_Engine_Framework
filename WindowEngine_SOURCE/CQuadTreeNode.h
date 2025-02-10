#pragma once
#include "CommonInclude.h"
namespace Framework
{
	class CQuadTree;
	class CColliderComponent;
	using namespace Maths;

	class CQuadTreeNode
	{
	public:
		enum class NodeIndex : int
		{
			UPPERLEFT = 0, // ��輱�� ��ġ�� �ʰ� ���� ����
			UPPERRIGHT,
			LOWERRIGHT,
			LOWERLEFT,
			STRADDLING,  // ��輱�� ��ģ ���
			OUTOFAREA // ���� ���� ��� ���. ( �Է� ���� )
		};

		CQuadTreeNode(CQuadTree* tree, CQuadTreeNode* parent, Vector2 center, Vector2 size, int depth);
		~CQuadTreeNode();

		void InsertAtDepth(CColliderComponent* item, int targetDepth);
		void Query(CColliderComponent* item, std::list<CQuadTreeNode*>& possibleNodes);

		void Clear();
		void Release();

		Vector2 GetCenter() const { return m_vecCenter; }
		Vector2 GetSize()	const { return m_vecSize; }
		Vector2 GetQSize()	const { return m_vecQSize; }

		std::list<CColliderComponent*> GetItemList() { return m_listItems; }

	private:
		std::list<CQuadTreeNode*> GetQuads(const Vector2& center, const Vector2& size);

		NodeIndex TestRegion(Vector2 center) const;
		bool Intersects(Vector2 center1, Vector2 size1, Vector2 center2, Vector2 size2);

		bool Split();

		bool IsSplitted()
		{
			return m_vecChildren.size() != 0;
		}




		std::vector<CQuadTreeNode*> m_vecChildren;
		std::list<CColliderComponent*> m_listItems;
		int m_iDepth;

		CQuadTree* m_pTree;
		CQuadTreeNode* m_pParent;

		Vector2 m_vecCenter;
		Vector2 m_vecSize;

		Vector2 _qbounds;
		Vector2 m_vecQSize;
	};
}


