#pragma once

enum class eMap
{
	Dev,
	Title,
	Play,

	//DontDestroy,
	Size,
};

enum class eLayer
{
	None,
	Sky,			//하늘
	BackGround,		//배경
	Environment,	//환경
	Monster,		//몬스터
	Character,		//캐릭터
	Item,			//아이템
	Font,			//대미지 폰트
	Size,
};

enum class eChannel
{
	BackGround,		//배경음
	Effect,			//효과음 ->스킬 , 스킬 타격음
	Monster,		//몬스터 ->타격음
	Player,			//플레이어 ->피격음 , 스킬 발동음
	UI,				//UI 효과음
	
	Size,
};