#pragma once
#include "..\\WindowEngine_SOURCE\\CCustomComponent.h"
namespace Framework
{
	class CPlayerInput :
		public CCustomComponent
	{
	public:
		CPlayerInput();
		virtual ~CPlayerInput();

	private:

		void Initialize() override;
		void Release() override;

		void Tick() override;
		void LastTick() override;

		void Render(HDC hdc) override;
	};


}
