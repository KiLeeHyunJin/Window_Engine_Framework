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
		T* pGameObject = new T(layerType);
		pCurScene->AddGameObject(pGameObject);
		pGameObject->SetName(name);
		return pGameObject;
	};

	static void Destroy(CGameObject* pObj)
	{
		pObj->Dead();
	}

	static void DontDestoryOnLoad(CGameObject* pGameObject)
	{
		CScene* pCurScene = CSceneManager::GetCurrentScene();
		pCurScene->EraseGameObject(pGameObject);
		CScene*  pDonDestoryScene = CSceneManager::GetDontDestoryScene();
		pDonDestoryScene->AddGameObject(pGameObject);
	}
}

