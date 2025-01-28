#include "CQuadTree.h"
#include "CQuadTreeNode.h"
#include "CColliderComponent.h"
#include "CCircleColliderComponent.h"
#include "CBoxColliderComponent.h"
#include "CTransformComponent.h"
namespace Framework
{
	CQuadTree::CQuadTree(Vector2 size)
	{
	}
	CQuadTree::~CQuadTree()
	{
	}
	void CQuadTree::Clear()
	{
		m_pRootNode->Clear();
	}

	void CQuadTree::Insert(CColliderComponent* pCollider)
	{
		m_pRootNode->InsertAtDepth(pCollider, GetTargetDepth(pCollider));
	}

	std::list<CColliderComponent*> CQuadTree::Query(CColliderComponent* queryItem)
	{
		std::list<CQuadTreeNode*> possibleNodes; //�浹 ���
		std::list<CColliderComponent*> interactions; //�浹 ���ɼ� ���� ������Ʈ

		m_pRootNode->Query(queryItem, possibleNodes); //�浹 ������ �����´�.

		for(auto node : possibleNodes) //��带 ��ȸ�ϸ� ���� ������Ʈ�� �����´�.
		{
			const std::list<CColliderComponent*>& items = node->GetItemList();
			for(auto& item : items)
			{
				interactions.push_back(item);
			}
		}
		return interactions;
	}

	int CQuadTree::GetTargetDepth(CColliderComponent* item)
	{
		// ���� ���� ��ü�� Depth�� �̸� ����
		float width = m_pRootNode->GetSize().x;
		Vector2 size = item->GetSize() * 0.5f;
		float maxHalfValue = size.x > size.y ? size.x : size.y;
		int targetDepth = (int)logf(width / maxHalfValue);
		if (targetDepth > m_iMaxDepth)
		{
			targetDepth = m_iMaxDepth;
		}

		return targetDepth;
	}
}