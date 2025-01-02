#pragma once
#include "..\\WindowEngine_SOURCE\\CScene.h"

namespace Framework
{
	class CSceneManager;

	class CPlayeScene :
		public CScene
	{
	public:


		friend CSceneManager;
	private:
		CPlayeScene();
		virtual ~CPlayeScene();

		// CScene을(를) 통해 상속됨
		void Initialize()		override;
		void Tick()				override;
		void LastTick()			override;
		void Render(HDC hDC)	override;
		void Release()			override;
	};


}


