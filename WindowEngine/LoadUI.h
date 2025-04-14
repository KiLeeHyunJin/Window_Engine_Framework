#pragma once
#include "..\\WindowEngine_SOURCE\\CUIManager.h"
#include "..\\WindowEngine_SOURCE\\CUIBase.h"

namespace Framework
{
	void LoadUI()
	{
		CUIBase* leftButton = new CUIBase();
		CUIBase* rightButton = new CUIBase();

		leftButton->SetLocalPosition(Maths::Vector2(300, 300));
		rightButton->SetLocalPosition(Maths::Vector2(150,150));
		//rightButton->SetDraggable(true);

		GET_SINGLE(UI).LoadUI(Enums::eUIType::Size, rightButton, true, false);
		GET_SINGLE(UI).LoadUI(Enums::eUIType::Button, leftButton, true, true);

	}
}