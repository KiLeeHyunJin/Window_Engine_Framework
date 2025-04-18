#include "CQuadTreeNode.h"
#include "CQuadTree.h"

#include "CRenderManager.h"

#include "CColliderComponent.h"
#include "CTransformComponent.h"
#include "CCameraComponent.h"
#include "CRenderer.h"

#include "CActor.h"
#include "Utils.h"
namespace Framework
{
	CQuadTreeNode::CQuadTreeNode(CQuadTree* tree, CQuadTreeNode* parent,const Vector2& center, const Vector2& size, int depth)
		: m_pTree(tree), m_pParent(parent), m_vecCenter(center), m_vecSize(size), m_iDepth(depth), check(false)
	{
		m_vecChildren.reserve(4);
		m_vecQSize = size * m_pTree->GetConstantK();
		const Maths::Vector2 halfSize = size * 0.5f;
		bounds.max = center + halfSize;
		bounds.min = center - halfSize;
	}

	CQuadTreeNode::~CQuadTreeNode()
	{	}
	
	void CQuadTreeNode::InsertAtDepth(CColliderComponent* item, int targetDepth)
	{
		if (m_iDepth < targetDepth) // 현재 깊이가 목표 깊이보다 얕으면 다음 깊이로 넘김.
		{
			if (Split())
			{
				//const CTransformComponent* pTr = item->GetOwner()->GetTransformComponent();
				Vector2 pos = item->GetOwner()->GetPosition();
				Vector2 offset = item->GetOffset();

				m_vecChildren[(int)TestRegion(offset + pos)]->InsertAtDepth(item, targetDepth);
			}
		}
		else if (m_iDepth == targetDepth) // 현재 깊이와 목표 깊이가 같으면 목록에 추가
		{
			m_listItems.push_back(item);
		}
	}

	void CQuadTreeNode::Query(CColliderComponent* item, std::vector<CQuadTreeNode*>& possibleNodes)
	{
		possibleNodes.push_back(this); //본인 노드를 저장한다.

		if (IsSplitted())
		{
			//const CTransformComponent* pTr = item->GetOwner()->GetTransformComponent();
			const Maths::Vector2 center = item->GetOwner()->GetPosition() + item->GetOffset();

			//std::list<CQuadTreeNode*> quads;

			for (const auto& child : m_vecChildren)
			{
				if (Maths::Vector2::Intersects(child->GetCenter(), child->GetQSize(), center, item->GetSize())) //느슨한 노드를 기준으로 충돌 체크 실시
				{
					child->Query(item, possibleNodes);
				}
			}
			//GetQuads(center, item->GetSize(), quads); //자식 노드들도 충돌 가능성이 있다면 참조 리스트에 저장시킨다.

			//for(const auto& quad : quads)
			//{
			//	quad->Query(item, possibleNodes);
			//}
		}
	}

	void CQuadTreeNode::Query(const Maths::Vector2& center,const Maths::Vector2& size, std::vector<CQuadTreeNode*>& possibleNodes)
	{
		possibleNodes.push_back(this); //본인 노드를 저장한다.

		if (IsSplitted())
		{
			//std::list<CQuadTreeNode*> quads;

			for (const auto& child : m_vecChildren)
			{
				if (Maths::Vector2::Intersects(child->GetCenter(), child->GetQSize(), center, size)) //느슨한 노드를 기준으로 충돌 체크 실시
				{
					child->Query(center, size, possibleNodes);
				}
			}

			//GetQuads(center, size, quads); //자식 노드 중도 충돌 가능성이 있다면 참조 리스트에 저장시킨다.

			//for (const auto& quad : quads) //자식 노드들을 돌면서 
			//{
			//	quad->Query(center, size, possibleNodes);
			//}
		}
	}


	void CQuadTreeNode::GetQuads(const Vector2& center, const Vector2& size, std::list<CQuadTreeNode*>& possibles)
	{
		for (const auto& child : m_vecChildren)
		{
			if (Maths::Vector2::Intersects(child->GetCenter(), child->GetQSize(), center, size)) //느슨한 노드를 기준으로 충돌 체크 실시
			{
				possibles.push_back(child);
			}
		}
	}

	bool CQuadTreeNode::Raycast(const Ray& ray, float& closestHit, CColliderComponent*& hitObject, const std::unordered_map<UINT32, CColliderComponent*>& ignores)
	{
		float tEnter = 0;
		//check = false;
		if (!bounds.Intersects(ray, tEnter) || tEnter > closestHit) //해당 노드와의 충돌 검사
		{
			return false;
		}
		if (tEnter > closestHit)
		{
			return false;
		}
		
		bool hit = false;
		//check = true;

		//std::unordered_set<CColliderComponent*> ignoreSet(ignores.begin(), ignores.end());

		for (auto obj : m_listItems)  // 오브젝트 충돌 검사
		{
			if (ActorLifeCheck(obj))
			{
				continue;
			}

			//ignores.find(obj->GetID())
			auto it = ignores.find(obj->GetColliderID());
			if (it != ignores.end())
			{
				continue;
			}


			float objNear;
			const Maths::Vector2 pos = obj->GetOwner()->GetPosition() + obj->GetOffset();
			const Maths::Vector2 halfSize = obj->GetSize() * 0.5f;

			Rect rect;

			rect.max = pos + halfSize;
			rect.min = pos - halfSize;

			if (rect.Intersects(ray, objNear) && objNear < closestHit) 
			{
				closestHit = objNear;
				hitObject = obj;
				hit = true;
			}
		}

		if (m_vecChildren.size() != 0)  // 자식들 순회
		{
			for (const auto& child : m_vecChildren) 
			{
				if (child) 
				{
					hit |= child->Raycast(ray, closestHit, hitObject, ignores);
				}
			}
		}

		return hit;
	}

	bool CQuadTreeNode::Raycast(const Ray& ray, float& closestHit, CColliderComponent*& hitObject, const std::vector<UINT>& checkLayers)
	{
		float tEnter = 0;
		//check = false;
		if (!bounds.Intersects(ray, tEnter) || tEnter > closestHit) //해당 노드와의 충돌 검사
		{
			return false;
		}
		if (tEnter > closestHit)
		{
			return false;
		}

		bool hit = false;
		Rect rect;
		//check = true;

		for (auto obj : m_listItems)  // 오브젝트 충돌 검사
		{
			if (ActorLifeCheck(obj))
			{
				continue;
			}

			const UINT layer = obj->GetOwner()->GetLayerType();
			auto iter = std::find(checkLayers.begin(), checkLayers.end(), layer); //무시 목록에 존재하면 점프
			if (iter == checkLayers.end())
			{
				continue;
			}

			float objNear;
			const Maths::Vector2 pos = obj->GetOwner()->GetPosition() + obj->GetOffset();
			const Maths::Vector2 halfSize = obj->GetSize() * 0.5f;

			rect.max = pos + halfSize;
			rect.min = pos - halfSize;

			if (rect.Intersects(ray, objNear) && objNear < closestHit)
			{
				closestHit = objNear;
				hitObject = obj;
				hit = true;
			}
		}

		if (m_vecChildren.size() != 0)  // 자식들 순회
		{
			for (const auto& child : m_vecChildren)
			{
				if (child)
				{
					hit |= child->Raycast(ray, closestHit, hitObject, checkLayers);
				}
			}
		}

		return hit;
	}

	bool CQuadTreeNode::ActorLifeCheck(CColliderComponent* pCollider)
	{
		const CActor* pObj = pCollider->GetOwner();
		return pObj->GetReserveDelete();
	}



	CQuadTreeNode::NodeIndex CQuadTreeNode::TestRegion(Vector2 center) const //저장 시킬 노드의 위치를 정한다.
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
		if (m_iDepth == m_pTree->GetMaxDepth()) // 지정한 최대 깊이에 도달
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
		m_listItems.clear();
		check = false;
		if (m_vecChildren.size() > 0)
		{
			for (auto node : m_vecChildren)
			{
				node->Clear();
			}
		}
		//m_vecChildren.clear();
	}

	void CQuadTreeNode::Release()
	{
		if (m_vecChildren.size() > 0)
		{
			for (auto node : m_vecChildren)
			{
				node->Release();
				delete(node);
			}
		}
		m_listItems.clear();
		m_vecChildren.clear();
	}

	void CQuadTreeNode::Render(HDC hdc)
	{
		Maths::Vector2 drawPos;

		if (m_vecChildren.size() > 0)
		{
			for (auto node : m_vecChildren)
			{
				node->Render(hdc);
			}
		}
		else
		{
			CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
			if (pCam != nullptr)
			{
				drawPos = pCam->CaluatePosition(m_vecCenter);
			}
			else
			{
				drawPos = m_vecCenter;
			}

			if (check == false)
			{
				m_colorFill = Color(0, 0, 255);
			}
			else
			{
				m_colorFill = Color(255, 0, 255);
			}
			COLORREF ref;
			memcpy(&ref, &m_colorFill, sizeof(COLORREF));
			HPEN newPen = CreatePen(BS_SOLID, 1, ref);
			//HBRUSH newBrush = CreateSolidBrush(NULL_BRUSH);
			HBRUSH newBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

			HPEN oldPen = (HPEN)SelectObject(hdc, newPen);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);


			Utils::DrawRect(hdc, drawPos, m_vecSize - Maths::Vector2(1,1));


			(HPEN)SelectObject(hdc, oldPen);
			(HBRUSH)SelectObject(hdc, oldBrush);

			DeleteObject(newPen);
			//DeleteObject(oldBrush);
		}

		return;

		if (m_listItems.size() > 0)
		{
			std::wstring str = L"";
			for (auto item : m_listItems)
			{
				str.append(item->GetName() + L", ");
			}
			//swprintf_s(str, 50, L"FPS : %d", str.c_str());
			int len = (int)wcsnlen_s(str.c_str(), 50);

			TextOut(hdc, static_cast<INT>(drawPos.x), static_cast<INT>(drawPos.y), str.c_str(), len);
		}
	}
}