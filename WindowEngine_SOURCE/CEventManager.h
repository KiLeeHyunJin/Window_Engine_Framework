#pragma once
#include "CommonInclude.h"
#include "CGameObject.h"

namespace Framework
{
	class CApplication;
	class CGameObject;

	class CEventManager
	{
	public:
		__forceinline static void DeleteGameObject(CGameObject* pObj) { pObj->SetReserveDelete(); }

		friend CApplication;
	private:
		CEventManager();
		~CEventManager();


	};
	using Event = CEventManager;
	using DeleteFunc = void(*)(CGameObject*); // 함수 포인터 - 정적 멤버 함수이므로, 객체 인스턴스 없이 호출 

	constexpr DeleteFunc Delete = &CEventManager::DeleteGameObject; //상수 함수 포인터 - constexpr을 붙였으므로 컴파일 타임 상수로 사용
}

