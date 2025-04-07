#pragma once
#include "CommonInclude.h"
#include "CEntity.h"

namespace Framework
{
	class CActor;
	class CSceneManager;
	class CEventManager;
	class CLayer;

	class CScene : public CEntity
	{
	public:


	protected:
		CScene();
		virtual ~CScene();

		virtual void Initialize()		= 0;
		virtual void Release()			= 0;
		
		virtual void TickComponent()				= 0;
		virtual void LastTickComponent()			= 0;

		virtual void Render(HDC hdc)	= 0;
		virtual void LastRender(HDC hdc) = 0;

		virtual void OnEnter()			= 0;
		virtual void OnExit()			= 0;


		friend CSceneManager;
		friend CEventManager;
	private:
		//씬 매니저
		void SceneInitialize();
		void SceneRelease();

		void SceneTickComponent();
		void SceneLastTickComponent();

		void SceneDestroy();
		void SceneRender(HDC hdc);


		//이벤트 매니저 
		void AddActor(CActor* pActor);
		bool EraseInLayer(CActor* pActor);

		const CLayer* GetLayer(UINT layer) const ;

		std::vector<CLayer*> m_vecLayer;
	};

}


