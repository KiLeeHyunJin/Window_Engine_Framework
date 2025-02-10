#pragma once
#include "..\\WindowEngine_SOURCE\\CUIManager.h"
#include "..\\WindowEngine_SOURCE\\CUIBase.h"

namespace Framework
{
	void LoadUI()
	{
		CUIBase* leftButton = new CUIBase();
		CUIBase* rightButton = new CUIBase();

		CUIManager::LoadUI(Enums::eUIType::Button, leftButton, true, true);
		CUIManager::LoadUI(Enums::eUIType::Size, rightButton, true, false);
	}
}