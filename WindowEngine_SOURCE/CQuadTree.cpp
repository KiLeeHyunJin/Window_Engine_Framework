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
		std::list<CQuadTreeNode*> possibleNodes; //충돌 노드
		std::list<CColliderComponent*> interactions; //충돌 가능성 게임 오브젝트

		m_pRootNode->Query(queryItem, possibleNodes); //충돌 노드들을 가져온다.

		for(auto node : possibleNodes) //노드를 순회하며 게임 오브젝트를 가져온다.
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
		// 현재 넣을 물체의 Depth를 미리 예측
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