#pragma once
#include "..\\WindowEngine_SOURCE\\CResourceManager.h"
#include "..\\WindowEngine_SOURCE\\CTexture.h"
#include "..\\WindowEngine_SOURCE\\CObjectManager.h"

namespace Framework
{
	void LoadResource()
	{

		GET_SINGLE(RESOURCE).LoadTexture(L"Room", L"..\\Resources\\Room.png");
		GET_SINGLE(RESOURCE).LoadTexture(L"Room1", L"..\\Resources\\Room1.png");
		GET_SINGLE(RESOURCE).LoadTexture(L"Room2", L"..\\Resources\\Room2.png");



	}

}