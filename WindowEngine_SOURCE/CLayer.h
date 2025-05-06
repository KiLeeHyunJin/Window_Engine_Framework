#pragma once
#include "CEntity.h"


namespace Framework
{

	//class CScene;
	class CActor;

	//namespace Manager
	//{
	//	class CCollisionManager;
	//	class CSceneManager;
	//	class CObjectManager;
	//}

	class CLayer :
		public CEntity
	{
	public :
		CLayer(UINT layer);
		virtual ~CLayer();

		void Initialize();
		void Release();
		void Delete();
		void Tick();
		void LastTick();
		void FixedTick();

		void Render(HDC hdc) const;



		void AddActor(CActor* pActor);
		bool EraseInIndex(CActor* pActor);

		void Clear();

		const std::vector<CActor*>& GetActor() const { return m_vecActor; }

		void ReleaseActor();
		void DeleteActor();

		//friend CScene;
		//friend Manager::CCollisionManager;
		//friend Manager::CSceneManager;
		//friend Manager::CObjectManager;
	private:
		UINT m_eLayer;
		std::vector<CActor*> m_vecActor;
		std::vector<CActor*> m_vecRemoveActor;
	};
}


