#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
namespace Framework
{
	class CApplication;
	class CGameObject;

	class CScene : public CEntity
	{
	public:
		CScene();
		virtual ~CScene();

		void Initialize();
		void Tick();
		void LastTick();
		void Render(HDC hDC);
		void Release();

		friend CApplication;
	private:

		vector<CGameObject*> m_vecGameObject;
	};

}


