#pragma once
#include "CSceneManager.h"
#include "CEventManager.h"

#include "Enums.h"
#include "CActor.h"
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
			static_assert(std::is_base_of<CActor, T>::value,L"Is Not Actor");

			CScene* pCurScene = CSceneManager::GetCurrentScene();
			if (pCurScene == nullptr)
			{
				return nullptr;
			}
			T* pActor = new T(layerType);
			EVENT::AddActor(pCurScene, pActor, dontDestory);
			pActor->SetName(name);

			//T* pComponent = pActor->AddComponent<T>();
			return pActor;
		};

		//static CActor* Instantiate(UINT layerType, const std::wstring& name, bool dontDestory = false)
		//{
		//	CScene* pCurScene = CSceneManager::GetCurrentScene();
		//	if (pCurScene == nullptr)
		//	{
		//		return nullptr;
		//	}
		//	CActor* pActor = new CActor(layerType);
		//	EVENT::AddActor(pCurScene, pActor, dontDestory);
		//	pActor->SetName(name);
		//	return pActor;
		//};

		static void Destroy(CActor* pObj)
		{
			const bool reserveDel = pObj->GetReserveDelete();
			if (reserveDel)
			{	return;		}

			EVENT::DeleteActor(pObj);
		}

		static void DontDestoryOnLoad(CActor* pActor, bool state = true)
		{
			EVENT::SetDontDestroyActor(pActor, state);
		}
	}
	
}

