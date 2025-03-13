#pragma once
#include "CSceneManager.h"
#include "CEventManager.h"

#include "Enums.h"
#include "CGameObject.h"

//#include "CLayer.h"


namespace Framework::Object
{
	template <typename T>
	static T* Instantiate(Enums::eLayerType layerType, std::wstring name, bool dontDestory = false)
	{
		CScene* pCurScene = CSceneManager::GetCurrentScene();
		if (pCurScene == nullptr)
		{
			return nullptr;
		}
		CGameObject* pGameObject = new CGameObject(layerType);
		EVENT::AddGameObject(pCurScene,pGameObject, dontDestory);
		pGameObject->SetName(name);

		T* pComponent = pGameObject->AddComponent<T>();
		return pComponent;
	};

	static CGameObject* Instantiate(Enums::eLayerType layerType, std::wstring name, bool dontDestory = false)
	{
		CScene* pCurScene = CSceneManager::GetCurrentScene();
		if (pCurScene == nullptr)
		{
			return nullptr;
		}
		CGameObject* pGameObject = new CGameObject(layerType);
		EVENT::AddGameObject(pCurScene, pGameObject, dontDestory);
		pGameObject->SetName(name);
		return pGameObject;
	};

	static void Destroy(CGameObject* pObj)
	{
		if (pObj->GetReserveDelete() == false)
		{
			Framework::Delete(pObj);
		}
		//Event::DeleteGameObject(pObj);
		//pObj->SetReserveDelete();
	}

	static void DontDestoryOnLoad(CGameObject* pGameObject)
	{
		if (pGameObject->GetDontDestroy() == false)
		{
			EVENT::SetDontDestroyGameObject(pGameObject);
		}
		//pCurScene->EraseGameObject(pGameObject);
		//CScene*  pDonDestoryScene = CSceneManager::GetDontDestoryScene();
		//pDonDestoryScene->AddGameObject(pGameObject);
	}
}

