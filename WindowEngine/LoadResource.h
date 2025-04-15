#pragma once
#include "..\\WindowEngine_SOURCE\\CResourceManager.h"
#include "..\\WindowEngine_SOURCE\\CTexture.h"
#include "..\\WindowEngine_SOURCE\\CObjectManager.h"
#include "..\\WindowEngine_SOURCE\\CSprite.h"

namespace Framework
{
	void LoadResource()
	{

		GET_SINGLE(RESOURCE).LoadTexture(L"Room", L"..\\Resources\\Room.png");
		const Resource::CTexture* room1Tx = GET_SINGLE(RESOURCE).LoadTexture(L"Room1", L"..\\Resources\\Room1.png");
		const Resource::CTexture* room2Tx = GET_SINGLE(RESOURCE).LoadTexture(L"Room2", L"..\\Resources\\Room2.png");

		GET_SINGLE(RESOURCE).CreateSprite(room1Tx, L"1", Maths::Vector2(0, 0),	Maths::Vector2(48,48));
		GET_SINGLE(RESOURCE).CreateSprite(room2Tx, L"2", Maths::Vector2(48, 0), Maths::Vector2(48, 48));


	}

}