#pragma once
#include "CComponent.h"

namespace Framework
{
	class CCustomComponent : public CComponent
	{
	protected:
		CCustomComponent();
		virtual ~CCustomComponent();

		friend CGameObject;
	private:

		void Initialize() override;
		void Release() override;

		void Tick() override;
		void LastTick() override;

		void Render(HDC hdc) override;
	};


}
