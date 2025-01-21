#pragma once
#include "CEntity.h"
#include "Enums.h"
#include "CGameObject.h"

namespace Framework
{
	class CCollisionManager;
	class CScene;
	class CLayer :
		public CEntity
	{
	public :


		friend CScene;
		friend CCollisionManager;
	private:
		CLayer(Enums::eLayerType layer);
		virtual ~CLayer();

		void Initialize();
		void Release();

		void Tick();
		void LastTick();

		void Render(HDC hdc);

		void AddGameObject(CGameObject* pGameObject);
		void RemoveGameObject(CGameObject* pGameObject);

		const std::list<CGameObject*> GetGameObject() const { return m_listGameObject; }

		void Destroy();

		Enums::eLayerType m_eLayer;
		std::list<CGameObject*> m_listGameObject;
		std::list<CGameObject*> m_listRemoveGameObject;
	};
}


