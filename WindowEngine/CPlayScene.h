#pragma once
#include "..\\WindowEngine_SOURCE\\CScene.h"

namespace Framework
{
	namespace Manager
	{
		class CSceneManager;
	}

	class CPlayScene :
		public CScene
	{
		friend Manager::CSceneManager;
	private:
		CPlayScene();
		virtual ~CPlayScene();

		// CScene��(��) ���� ��ӵ�
		void Initialize()		override;
		void Tick()				override;
		void LastTick()			override;
		void Render(HDC hdc)	override;
		void Release()			override;

		// CScene��(��) ���� ��ӵ�
		void OnEnter() override;
		void OnExit() override;

		std::vector<CActor*> m_list;

		// CScene��(��) ���� ��ӵ�
		//void LastRender(HDC hdc) override;
	};


}


