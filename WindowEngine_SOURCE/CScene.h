#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
#include "CLayer.h"

namespace Framework
{
	//class CApplication;
	class CGameObject;
	class CSceneManager;

	class CScene : public CEntity
	{
	public:
		void AddGameObject(CGameObject* pGameObject, Enums::eLayerType layer);

	protected:
		CScene();
		virtual ~CScene();

		virtual void Initialize()		= 0;
		virtual void Release()			= 0;
		
		virtual void Tick()				= 0;
		virtual void LastTick()			= 0;

		virtual void Render(HDC hdc)	= 0;

		virtual void OnEnter()			= 0;
		virtual void OnExit()			= 0;


		friend CSceneManager;
	private:

		void SceneInitialize();
		void SceneRelease();
		void SceneTick();
		void SceneLastTick();
		void SceneRender(HDC hdc);

		//std::vector<CGameObject*> m_vecGameObject;
		std::vector<CLayer*> m_vecLayer;
	};

}


