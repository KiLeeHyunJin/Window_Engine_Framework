#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
namespace Framework
{
	//class CApplication;
	class CGameObject;
	class CSceneManager;

	class CScene : public CEntity
	{
	public:

		//friend CApplication;
		friend CSceneManager;
	protected:
		CScene();
		virtual ~CScene();

		virtual void Initialize();
		virtual void Release();

		virtual void Tick();
		virtual void LastTick();

		virtual void Render(HDC hDC);

		void AddGameObject(CGameObject* pGameObject);

	private:

		vector<CGameObject*> m_vecGameObject;
	};

}


