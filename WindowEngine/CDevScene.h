#pragma once
#include "..\\WindowEngine_SOURCE\\CScene.h"

namespace Framework
{
	namespace Manager
	{
		class CSceneManager;
	}

	class CDevScene :
		public CScene
	{
	public:

		friend Manager::CSceneManager;
	private:
		CDevScene();
		virtual ~CDevScene();

		// CScene��(��) ���� ��ӵ�
		void Initialize()		override;
		void Tick()				override;
		void LastTick()			override;
		void Render(HDC hdc)	override;
		void Release()			override;

		// CScene��(��) ���� ��ӵ�
		void OnEnter() override;
		void OnExit() override;



		// CScene��(��) ���� ��ӵ�
		//void LastRender(HDC hdc) override;

	};

}

