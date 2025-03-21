#pragma once
#include "CEntity.h"
#include "Enums.h"

namespace Framework
{
	class CCollisionManager;
	class CSceneManager;
	class CScene;
	class CGameObject;

	class CLayer :
		public CEntity
	{
	public :


		friend CScene;
		friend CCollisionManager;
		friend CSceneManager;
	private:
		CLayer(UINT layer);
		virtual ~CLayer();

		void Initialize();
		void Release();

		void Tick();
		void LastTick();

		void Render(HDC hdc) const;

		void AddGameObject(CGameObject* pGameObject);
		bool EraseInIndex(CGameObject* pGameObject);

		const std::vector<CGameObject*>& GetGameObject() const { return m_listGameObject; }

		void Destroy();

		UINT m_eLayer;
		std::vector<CGameObject*> m_listGameObject;
		std::vector<CGameObject*> m_listRemoveGameObject;
	};
}


