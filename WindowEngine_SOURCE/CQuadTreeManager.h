#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CCollisionManager;
	class CColliderComponent;
	class CQuadTree;
	class CGameObjcet;


	class CQuadTreeManager
	{
	public:

		friend CCollisionManager;
	private:
		CQuadTreeManager();
		~CQuadTreeManager();

		static void Initialize(const Maths::Vector2& size, int maxDepth, float constrantK);
		static void Insert(CColliderComponent* pCollider);

		static bool Raycast(const Ray& ray, CColliderComponent*& hitObject, const std::vector<CColliderComponent*>& ignores);
		static bool Raycast(const Ray& ray, CColliderComponent*& hitObject, const std::vector<UINT>& checkLayers);

		static const std::vector<CColliderComponent*>& Query(CColliderComponent* queryItem);
		static const std::vector<CColliderComponent*>& Query(const Maths::Vector2& center, const Maths::Vector2& size);

		static void Clear();
		static void Release();
		static void Render(HDC hdc);
		static CQuadTree* m_pQuadTree;
	};

}

