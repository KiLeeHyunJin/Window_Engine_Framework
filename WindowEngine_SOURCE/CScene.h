#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
#include "CLayer.h"

namespace Framework
{
	class CGameObject;
	class CSceneManager;
	class CEventManager;

	class CScene : public CEntity
	{
	public:


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
		friend CEventManager;
	private:
		void SceneInitialize();
		void SceneRelease();

		void SceneTick();
		void SceneLastTick();

		void SceneDestroy();
		void SceneRender(HDC hdc);

		void AddGameObject(CGameObject* pGameObject);
		bool EraseInLayer(CGameObject* pGameObject);
		//void InsertInLayer(CGameObject* pGameObject);
		const CLayer* GetLayer(Enums::eLayerType layer) const { return m_vecLayer[(UINT)layer]; }
		//std::vector<CGameObject*> m_vecGameObject;
		std::vector<CLayer*> m_vecLayer;
	};

}


