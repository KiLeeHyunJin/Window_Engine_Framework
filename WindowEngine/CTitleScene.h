#pragma once
#include "..\\WindowEngine_SOURCE\\CScene.h"

namespace Framework
{
    class CSceneManager;


    class CTitleScene :
        public CScene
    {
        friend CSceneManager;
    private:
        CTitleScene();
        virtual ~CTitleScene();

        void Initialize()		override;
        void Tick()				override;
        void LastTick()			override;
        void Render(HDC hdc)	override;
        void Release()			override;

        // CScene을(를) 통해 상속됨
        void OnEnter() override;
        void OnExit() override;
    };
}


