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
	static T* Instantiate(Enums::eLayerType layerType, std::wstring name)
	{
		CScene* pCurScene = CSceneManager::GetCurrentScene();
		if (pCurScene == nullptr)
		{
			return nullptr;
		}
		T* pGameObject = new T();
		pCurScene->AddGameObject(pGameObject, layerType);
		pGameObject->SetName(name);
		return pGameObject;
	};

	static void Destroy(CGameObject* pObj)
	{
		pObj->Dead();
	}
}

