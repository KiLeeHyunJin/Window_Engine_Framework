#pragma once
#include "..\\WindowEngine_SOURCE\\CResourceManager.h"

#include "..\\WindowEngine_SOURCE\\CTexture.h"
#include "..\\WindowEngine_SOURCE\\CSound.h"
#include "..\\WindowEngine_SOURCE\\CSprite.h"

namespace Framework
{

	void LoadTexture()
	{
		return;
		const Resource::CTexture* roomTx	= GET_SINGLE(RESOURCE).LoadTexture(L"Room"	, L"..\\Resources\\Textures\\Room.png");
		const Resource::CTexture* room1Tx	= GET_SINGLE(RESOURCE).LoadTexture(L"Room1"	, L"..\\Resources\\Textures\\Room1.png");
		const Resource::CTexture* room2Tx	= GET_SINGLE(RESOURCE).LoadTexture(L"Room2"	, L"..\\Resources\\Textures\\Room2.png");

		GET_SINGLE(RESOURCE).CreateSprite(room1Tx, L"1", Maths::Vector2(0	, 0)	, Maths::Vector2(24	, 24));
		GET_SINGLE(RESOURCE).CreateSprite(room2Tx, L"2", Maths::Vector2(24	, 0)	, Maths::Vector2(24	, 24));
	}

	void LoadSound()
	{
		std::vector<SOUND::eSoundGroup> groups((UINT)eChannel::Size);
		groups[(UINT)eChannel::BackGround	] = SOUND::eSoundGroup::Background;
		groups[(UINT)eChannel::Effect		] = SOUND::eSoundGroup::Effect;
		groups[(UINT)eChannel::Monster		] = SOUND::eSoundGroup::Effect;
		groups[(UINT)eChannel::Player		] = SOUND::eSoundGroup::Effect;
		groups[(UINT)eChannel::UI			] = SOUND::eSoundGroup::UI;
		GET_SINGLE(SOUND).SetGroup(groups);

		GET_SINGLE(RESOURCE).LoadSound(L"sound2", L"..\\Resources\\Sounds\\Success.wav", (UINT)eChannel::Effect);

	}


	void LoadResource()
	{
		LoadTexture();
		LoadSound();
	}
}