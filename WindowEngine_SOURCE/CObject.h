#pragma once
#include "Enums.h"
#include "CGameObject.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "CComponent.h"
#include "CLayer.h"


namespace Framework::Object
{
	template <typename T>
	static T* Instantiate(Enums::eLayerType layerType)
	{
		T* pGameObject = new T();
		CScene* pCurScene = CSceneManager::GetCurrentScene();
		if (pCurScene == nullptr)
		{
			return nullptr;
		}
		pCurScene->AddGameObject(pGameObject, layerType);
		return pGameObject;
	};

}

