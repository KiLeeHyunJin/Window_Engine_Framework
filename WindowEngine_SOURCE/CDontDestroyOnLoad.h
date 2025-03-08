#pragma once
#include "CScene.h"

namespace Framework
{

	class CDontDestroyOnLoad : public CScene
	{
	public:
		CDontDestroyOnLoad();
		~CDontDestroyOnLoad();

	private:
		virtual void Initialize()	override;
		virtual void Release()		override;

		virtual void Tick()			override;
		virtual void LastTick()		override;

		virtual void Render(HDC hdc) override;

		virtual void OnEnter()		override;
		virtual void OnExit()		override;

	};
}
