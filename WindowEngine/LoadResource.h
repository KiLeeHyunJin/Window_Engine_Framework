#pragma once
#include "..\\WindowEngine_SOURCE\\CResourceManager.h"
#include "..\\WindowEngine_SOURCE\\CTexture.h"

namespace Framework
{
	void LoadResource()
	{
		Framework::Resource::CResourceManager::Load<Resource::CTexture>(L"Room", L"Resources\\Room.png");
	}

}