#pragma once
#include "CSceneManager.h"
#include "CEventManager.h"

#include "Enums.h"
#include "CGameObject.h"
#include "CScene.h"

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
		CGameObject* pGameObject = new CGameObject(layerType);
		pCurScene->AddGameObject(pGameObject);
		pGameObject->SetName(name);

		T* pComponent = pGameObject->AddComponent<T>();
		return pComponent;
	};

	static CGameObject* Instantiate(Enums::eLayerType layerType, std::wstring name)
	{
		CScene* pCurScene = CSceneManager::GetCurrentScene();
		if (pCurScene == nullptr)
		{
			return nullptr;
		}
		CGameObject* pGameObject = new CGameObject(layerType);
		pCurScene->AddGameObject(pGameObject);
		pGameObject->SetName(name);
		return pGameObject;
	};

	static void Destroy(CGameObject* pObj)
	{
		//Event::DeleteGameObject(pObj);
		Framework::Delete(pObj);
		//pObj->SetReserveDelete();
	}

	static void DontDestoryOnLoad(CGameObject* pGameObject)
	{
		CScene* pCurScene = CSceneManager::GetCurrentScene();
		pCurScene->EraseGameObject(pGameObject);
		CScene*  pDonDestoryScene = CSceneManager::GetDontDestoryScene();
		pDonDestoryScene->AddGameObject(pGameObject);
	}
}

