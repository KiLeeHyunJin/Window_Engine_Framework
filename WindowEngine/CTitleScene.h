#pragma once
#include "..\\WindowEngine_SOURCE\\CScene.h"

namespace Framework
{
    namespace Manager
    {
        class CSceneManager;
    }

    class CTitleScene :
        public CScene
    {
    public: 
        CTitleScene();
        virtual ~CTitleScene();



        // CScene��(��) ���� ��ӵ�
        void OnEnter() override;
        void OnExit() override;
    private:
        void Initialize()		override;
        void Tick()				override;
        void LastTick()			override;
        void Render(HDC hdc)	override;
        void Release()			override;

        // CScene��(��) ���� ��ӵ�
        //void LastRender(HDC hdc) override;
    };
}


