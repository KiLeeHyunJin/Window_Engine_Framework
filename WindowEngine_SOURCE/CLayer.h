#pragma once
#include "CEntity.h"
#include "Enums.h"
#include "CGameObject.h"

namespace Framework
{
	class CLayer :
		public CEntity
	{
	public :
		CLayer(Enums::eLayerType layer);
		virtual ~CLayer();

		void Initialize();
		void Release();

		void Tick();
		void LastTick();

		void Render(HDC hdc);

		void AddGameObject(CGameObject* pGameObject);

	private:
		Enums::eLayerType m_eLayer;
		std::list<CGameObject*> m_listGameObject;
	};
}


