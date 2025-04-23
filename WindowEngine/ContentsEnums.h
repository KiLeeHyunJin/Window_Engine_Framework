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
	Sky,			//�ϴ�
	BackGround,		//���
	Environment,	//ȯ��
	Monster,		//����
	Character,		//ĳ����
	Item,			//������
	Font,			//����� ��Ʈ
	Size,
};

enum class eChannel
{
	BackGround,		//�����
	Effect,			//ȿ���� ->��ų , ��ų Ÿ����
	Monster,		//���� ->Ÿ����
	Player,			//�÷��̾� ->�ǰ��� , ��ų �ߵ���
	UI,				//UI ȿ����
	
	Size,
};