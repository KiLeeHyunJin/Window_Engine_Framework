#pragma once
#include "..\\WindowEngine_SOURCE\\CResourceManager.h"
#include "..\\WindowEngine_SOURCE\\CTexture.h"

namespace Framework
{
	void LoadResource()
	{
		Framework::Resource::CResourceManager::LoadTexture(L"Room", L"..\\Resources\\Room.png");
		Framework::Resource::CResourceManager::LoadTexture(L"Room1", L"..\\Resources\\Room1.png");
		Framework::Resource::CResourceManager::LoadTexture(L"Room2", L"..\\Resources\\Room2.png");



	}

}