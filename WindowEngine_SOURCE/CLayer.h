#pragma once
#include "CEntity.h"
#include "Enums.h"

namespace Framework
{
	class CCollisionManager;
	class CSceneManager;
	class CScene;
	class CActor;

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

		void AddActor(CActor* pActor);
		bool EraseInIndex(CActor* pActor);

		const std::vector<CActor*>& GetActor() const { return m_listActor; }

		void Destroy();

		UINT m_eLayer;
		std::vector<CActor*> m_listActor;
		std::vector<CActor*> m_listRemoveActor;
	};
}


