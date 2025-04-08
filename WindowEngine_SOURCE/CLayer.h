#pragma once
#include "CEntity.h"
#include "Enums.h"

namespace Framework
{

	class CScene;
	class CActor;

	namespace Manager
	{
		class CCollisionManager;
		class CSceneManager;
		class CObjectManager;
	}

	class CLayer :
		public CEntity
	{
	public :


		friend CScene;
		friend Manager::CCollisionManager;
		friend Manager::CSceneManager;
		friend Manager::CObjectManager;
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

		void Clear();

		const std::vector<CActor*>& GetActor() const { return m_vecActor; }

		void Destroy();

		UINT m_eLayer;
		std::vector<CActor*> m_vecActor;
		std::vector<CActor*> m_vecRemoveActor;
	};
}


