#include "CQuadTreeNode.h"
#include "CQuadTree.h"
#include "CColliderComponent.h"
#include "CGameObject.h"
#include "CTransformComponent.h"
namespace Framework
{
	CQuadTreeNode::CQuadTreeNode(CQuadTree* tree, CQuadTreeNode* parent, Vector2 center, Vector2 size, int depth) :m_vecChildren(4)
	{
		m_pTree = tree;
		m_pParent = parent;
		m_vecCenter = center;
		m_vecSize = size;
		m_vecQSize = size * m_pTree->GetConstantK();

		m_iDepth = depth;

	}
	CQuadTreeNode::~CQuadTreeNode()
	{
	}
	void CQuadTreeNode::InsertAtDepth(CColliderComponent* item, int targetDepth)
	{
		if (m_iDepth < targetDepth) // ���� ���̰� ��ǥ ���̺��� ������ ���� ���̷� �ѱ�.
		{
			if (Split())
			{
				const CTransformComponent* pTr = item->GetOwner()->GetTransformComponent();
				Vector2 pos = pTr->GetPos();
				Vector2 offset = item->GetOffset();
				m_vecChildren[(int)TestRegion(offset + pos)]->InsertAtDepth(item, targetDepth);
			}
		}
		else if (m_iDepth == targetDepth) // ���� ���̿� ��ǥ ���̰� ������ ��Ͽ� �߰�
		{
			m_listItems.push_back(item);
		}
	}
	void CQuadTreeNode::Query(CColliderComponent* item, std::list<CQuadTreeNode*>& possibleNodes)
	{
		possibleNodes.push_back(this); //���� ��带 �����Ѵ�.

		if (IsSplitted())
		{
			const CTransformComponent* pTr = item->GetOwner()->GetTransformComponent();
			const Maths::Vector2 center = pTr->GetPos() + item->GetOffset();
			const std::list<CQuadTreeNode*>& quads = GetQuads(center, item->GetSize()); //�ڽ� ���鵵 �浹 ���ɼ��� �ִٸ� �����Ų��.
			for(const auto& quad : quads)
			{
				quad->Query(item, possibleNodes);
			}
		}
	}

	std::list<CQuadTreeNode*> CQuadTreeNode::GetQuads(const Vector2& center,const Vector2& size)
	{
		std::list<CQuadTreeNode*> quads;

		for(const auto& child : m_vecChildren)
		{
			if (Maths::Vector2::Intersects(child->GetCenter(), child->GetQSize(), center, size)) //������ ��带 �������� �浹 üũ �ǽ�
			{
				quads.push_back(child);
			}
		}
		return quads;
	}

	CQuadTreeNode::NodeIndex CQuadTreeNode::TestRegion(Vector2 center) //���� ��ų ����� ��ġ�� ���Ѵ�.
	{
		bool negX = center.x <= m_vecCenter.x;
		bool negY = center.y <= m_vecCenter.y;
		bool posX = center.x  > m_vecCenter.x;
		bool posY = center.y  > m_vecCenter.y;

		if (negX && posY)
		{
			return CQuadTreeNode::NodeIndex::UPPERLEFT;
		}

		if (posX && posY)
		{
			return CQuadTreeNode::NodeIndex::UPPERRIGHT;
		}

		if (posX && negY)
		{
			return CQuadTreeNode::NodeIndex::LOWERRIGHT;
		}

		if (negX && negY)
		{
			return CQuadTreeNode::NodeIndex::LOWERLEFT;
		}

		return CQuadTreeNode::NodeIndex::OUTOFAREA;
	}

	bool CQuadTreeNode::Split()
	{
		if (m_iDepth == m_pTree->GetMaxDepth()) // ������ �ִ� ���̿� ����
		{
			return false;
		}

		if (IsSplitted() == false)
		{
			const int newDepth = m_iDepth + 1;
			const Vector2 newBoundsSize = m_vecSize * 0.5f;
			Vector2 centerOffset = newBoundsSize * 0.5f;
			//[-x, +y] // UPPERLEFT
			centerOffset.x *= -1.0f;
			m_vecChildren.push_back(new CQuadTreeNode(m_pTree, this, m_vecCenter + centerOffset, newBoundsSize, newDepth));

			//[+x, +y] // UPPERRIGHT
			centerOffset.x *= -1.0f;
			m_vecChildren.push_back(new CQuadTreeNode(m_pTree, this, m_vecCenter + centerOffset, newBoundsSize, newDepth));

			//[-x, -y] // LOWERRIGHT
			centerOffset.y *= -1.0f;
			m_vecChildren.push_back(new CQuadTreeNode(m_pTree, this, m_vecCenter + centerOffset, newBoundsSize, newDepth));

			//[+x, -y] // LOWERLEFT
			centerOffset.x *= -1.0f;
			m_vecChildren.push_back(new CQuadTreeNode(m_pTree, this, m_vecCenter + centerOffset, newBoundsSize, newDepth));
		}

		return true;
	}

	bool CQuadTreeNode::Intersects(Vector2 center1, Vector2 size1, Vector2 center2, Vector2 size2)
	{
		if (Maths::Abs(center1.x - center2.x) < Maths::Abs((size1.x + size2.x) * 0.5f) &&
			Maths::Abs(center1.y - center2.y) < Maths::Abs((size1.y + size2.y) * 0.5f))
		{
			return true;
		}
		return false;
		return false;
	}

	

	void CQuadTreeNode::Clear()
	{
		if (m_vecChildren.size() > 0)
		{
			for (auto node : m_vecChildren)
			{
				node->Clear();
			}
		}
		m_listItems.clear();
		m_vecChildren.clear();
	}
}