#include "CQuadTree.h"
#include "CQuadTreeNode.h"
#include "CColliderComponent.h"
#include "CCircleColliderComponent.h"
#include "CBoxColliderComponent.h"
#include "CTransformComponent.h"
#include "CGameObject.h"

namespace Framework
{
	CQuadTree::CQuadTree(Vector2 size, int maxDepth, float constantK) : 
		m_iMaxDepth(maxDepth), m_fConstantK(constantK)
	{
		m_pRootNode = new CQuadTreeNode(this, nullptr, Maths::Vector2::Zero, size, 2);
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

	const std::list<CColliderComponent*>& CQuadTree::Query(CColliderComponent* queryItem)
	{
		const CTransformComponent* pTr = queryItem->GetOwner()->GetTransformComponent();
		const Maths::Vector2 center = pTr->GetPos() + queryItem->GetOffset();
		const Maths::Vector2 size = queryItem->GetSize();

		return Query(center, size);
	}

	const std::list<CColliderComponent*>& CQuadTree::Query(const Maths::Vector2& center, const Maths::Vector2& size)
	{
		m_pPossibleNodes.clear(); //�浹 ���
		m_pCollisionList.clear();

		m_pRootNode->Query(center, size, m_pPossibleNodes); //�浹 ������ �����´�.

		for (const auto& node : m_pPossibleNodes) //��带 ��ȸ�ϸ� ���� ������Ʈ�� �����´�.
		{
			const std::list<CColliderComponent*>& items = node->GetItemList();
			for (const auto& item : items)
			{
				m_pCollisionList.push_back(item);
			}
		}
		return m_pCollisionList;
	}

	bool CQuadTree::Raycast(const Ray& ray, float& closestHit, CColliderComponent& hitObject, const std::vector<CColliderComponent*>& ignores)
	{
		return m_pRootNode->Raycast(ray, closestHit, hitObject, ignores);
	}

	bool CQuadTree::Raycast(const Ray& ray, float& closestHit, CColliderComponent& hitObject, const std::vector<Enums::eLayerType>& checkLayer)
	{
		return false;
	}

	void CQuadTree::Render(HDC hdc)
	{
		m_pRootNode->Render(hdc);
	}

	void CQuadTree::Release()
	{
		if (m_pRootNode != nullptr)
		{
			m_pRootNode->Release();
			delete m_pRootNode;
		}
	}

	int CQuadTree::GetTargetDepth(CColliderComponent* item)
	{
		// ���� ���� ��ü�� Depth�� �̸� ����
		const float width = m_pRootNode->GetSize().x;

		const Vector2 size = item->GetSize() * 0.5f;
		const float maxHalfValue = size.x > size.y ? size.x : size.y;

		int targetDepth = static_cast<int>(std::floor(std::log(width / maxHalfValue) / std::log(2.0)));

		if (targetDepth > m_iMaxDepth)
		{
			targetDepth = m_iMaxDepth;
		}

		return targetDepth;
	}
}