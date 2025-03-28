#pragma once
#include "CSceneManager.h"
#include "CEventManager.h"

#include "Enums.h"
#include "CGameObject.h"
//#include "CComponent.h"

//#include "CLayer.h"


namespace Framework//::Object
{
	class CComponent;

	namespace Object
	{
		template <typename T>
		static T* Instantiate(UINT layerType, const std::wstring& name, bool dontDestory = false)
		{
			static_assert(std::is_base_of<CComponent, T>::value,L"Is Not Component");

			CScene* pCurScene = CSceneManager::GetCurrentScene();
			if (pCurScene == nullptr)
			{
				return nullptr;
			}
			CGameObject* pGameObject = new CGameObject(layerType);
			EVENT::AddGameObject(pCurScene, pGameObject, dontDestory);
			pGameObject->SetName(name);

			T* pComponent = pGameObject->AddComponent<T>();
			return pComponent;
		};

		static CGameObject* Instantiate(UINT layerType, const std::wstring& name, bool dontDestory = false)
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
			const bool reserveDel = pObj->GetReserveDelete();
			if (reserveDel)
			{	return;		}

			EVENT::DeleteGameObject(pObj);
		}

		static void DontDestoryOnLoad(CGameObject* pGameObject, bool state = true)
		{
			EVENT::SetDontDestroyGameObject(pGameObject, state);
		}
	}
	
}

