#pragma once

namespace Framework
{
	class CCollisionManager;
	class CColliderComponent;
	class CQuadTreeManager
	{
	public:



		friend CCollisionManager;
	private:
		CQuadTreeManager();
		~CQuadTreeManager();

		void Insert(CColliderComponent* pCollider);

	};

}

