#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
#include "CLayer.h"

namespace Framework
{
	//class CApplication;
	class CGameObject;
	class CSceneManager;
	class CCollisionManager;

	class CScene : public CEntity
	{
	public:
		void AddGameObject(CGameObject* pGameObject);
		void EraseGameObject(CGameObject* pGameObject);

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
		friend CCollisionManager;
	private:
		void SceneInitialize();
		void SceneRelease();

		void SceneTick();
		void SceneLastTick();

		void SceneDestroy();
		void SceneRender(HDC hdc);

		const CLayer* GetLayer(Enums::eLayerType layer) const { return m_vecLayer[(UINT)layer]; }
		//std::vector<CGameObject*> m_vecGameObject;
		std::vector<CLayer*> m_vecLayer;
	};

}


