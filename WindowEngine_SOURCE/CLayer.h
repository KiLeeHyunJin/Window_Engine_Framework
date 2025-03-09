#pragma once
#include "CEntity.h"
#include "Enums.h"
#include "CGameObject.h"

namespace Framework
{
	class CCollisionManager;
	class CSceneManager;
	class CScene;

	class CLayer :
		public CEntity
	{
	public :


		friend CScene;
		friend CCollisionManager;
		friend CSceneManager;
	private:
		CLayer(Enums::eLayerType layer);
		virtual ~CLayer();

		void Initialize();
		void Release();

		void Tick();
		void LastTick();

		void Render(HDC hdc) const;

		void AddGameObject(CGameObject* pGameObject);
		void EraseGameObject(CGameObject* pGameObject);

		const std::vector<CGameObject*>& GetGameObject() const { return m_listGameObject; }

		void Destroy();

		Enums::eLayerType m_eLayer;
		std::vector<CGameObject*> m_listGameObject;
		std::vector<CGameObject*> m_listRemoveGameObject;
	};
}


