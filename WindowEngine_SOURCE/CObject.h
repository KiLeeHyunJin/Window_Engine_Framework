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
		CScene* pCurScene = CSceneManager::GetCurrentScene();
		if (pCurScene == nullptr)
		{
			return nullptr;
		}
		T* pGameObject = new T();
		pCurScene->AddGameObject(pGameObject, layerType);
		return pGameObject;
	};

}

