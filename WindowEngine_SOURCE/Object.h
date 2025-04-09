#pragma once
#include "CEventManager.h"
#include "CObjectManager.h"

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

			T* pActor = new T(layerType);
			GET_SINGLE(EVENT).AddActor(pActor, dontDestory);
			pActor->SetName(name);
			return pActor;
		};

		static void Destroy(CActor* pObj)
		{
			const bool reserveDel = pObj->GetReserveDelete();
			if (reserveDel)
			{	return;		}

			GET_SINGLE(EVENT).DeleteActor(pObj);
		}

		static void DontDestoryOnLoad(CActor* pActor, bool state = true)
		{	GET_SINGLE(EVENT).SetDontDestroyActor(pActor, state);	}

		__forceinline static CActor* GetActor(UINT32 actorID)
		{		return GET_SINGLE(OBJECT).GetActor(actorID);		}
	}
	
}

