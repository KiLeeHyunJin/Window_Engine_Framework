#pragma once
#include "CComponent.h"

namespace Framework
{
	class CCustomComponent : public CComponent
	{
	public:
		CCustomComponent();
		virtual ~CCustomComponent();

		void Initialize() override;
		void Release() override;

		void Tick() override;
		void LastTick() override;

		void Render(HDC hdc) override;
	};


}
