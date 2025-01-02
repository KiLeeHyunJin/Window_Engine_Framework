#pragma once

#include "..\\WindowEngine_SOURCE\\CSceneManager.h"
#include "CPlayeScene.h"

namespace Framework
{
	void LoadScenes()
	{
		CSceneManager::CreateScene<CPlayeScene>(L"PlayeScene");

		//CSceneManager::CreateScene(L"PlayeScene", new CPlayeScene); //���� ���Ŵ����� �����ϰ�����

		CSceneManager::LoadScene(L"PlayeScene");
	}

}