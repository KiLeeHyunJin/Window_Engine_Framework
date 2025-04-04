#pragma once
#include "CommonInclude.h"
#include "Structs.h"

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
		void Query(CColliderComponent* item, std::vector<CQuadTreeNode*>& possibleNodes);
		void Query(const Maths::Vector2& center, const Maths::Vector2& size, std::vector<CQuadTreeNode*>& possibleNodes);

		bool Raycast(const Ray& ray, float& closestHit, CColliderComponent*& hitObject, const std::unordered_map<UINT32, CColliderComponent*>& ignores);
		bool Raycast(const Ray& ray, float& closestHit, CColliderComponent*& hitObject, const std::vector<UINT>& checkLayers);


		void Clear();
		void Release();
		void Render(HDC hdc);
		
		const Vector2& GetCenter()  const { return m_vecCenter; }
		const Vector2& GetSize()	const { return m_vecSize; }
		const Vector2& GetQSize()	const { return m_vecQSize; }

		std::list<CColliderComponent*>& GetItemList() { return m_listItems; }

	private:
		void GetQuads(const Vector2& center, const Vector2& size, std::list<CQuadTreeNode*>& possibles);

		__forceinline NodeIndex TestRegion(Vector2 center) const;
		__forceinline bool Intersects(Vector2 center1, Vector2 size1, Vector2 center2, Vector2 size2);
		__forceinline bool ActorLifeCheck(CColliderComponent* pCollider);
		__forceinline bool Split();

		__forceinline bool IsSplitted()		const	{	return m_vecChildren.size() != 0;	}

		std::vector<CQuadTreeNode*> m_vecChildren;
		std::list<CColliderComponent*> m_listItems;
		int m_iDepth;

		CQuadTree* m_pTree;
		CQuadTreeNode* m_pParent;

		Vector2 m_vecCenter;
		Vector2 m_vecSize;

		Vector2 _qbounds;
		Vector2 m_vecQSize;
		Color m_colorFill;
		bool check;
		Rect bounds;

	};
}


