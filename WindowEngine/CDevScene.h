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
		CDevScene();
		virtual ~CDevScene();



		// CScene을(를) 통해 상속됨
		void OnEnter() override;
		void OnExit() override;
		//friend Manager::CSceneManager;
	private:


		// CScene을(를) 통해 상속됨
		void Initialize()		override;
		void Tick()				override;
		void LastTick()			override;
		void Render(HDC hdc)	override;
		void Release()			override;



		// CScene을(를) 통해 상속됨
		//void LastRender(HDC hdc) override;

	};

}

