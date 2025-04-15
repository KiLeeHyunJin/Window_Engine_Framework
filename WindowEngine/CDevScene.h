#pragma once
#include "..\\WindowEngine_SOURCE\\CScene.h"
#include "..\\WindowEngine_SOURCE\\CTilemap.h"
#include "..\\WindowEngine_SOURCE\\CTilemapActor.h"

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

		void LoadFile(const std::wstring& path);
		void SaveFile(const std::wstring& path);

		void SetTilemapActor(CActor* actor);

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

		CTilemapActor* m_pTilemapActor	 = nullptr;

		// CScene을(를) 통해 상속됨
		//void LastRender(HDC hdc) override;

	};

}

