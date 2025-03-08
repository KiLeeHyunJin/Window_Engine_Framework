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
	using DeleteFunc = void(*)(CGameObject*); // �Լ� ������ - ���� ��� �Լ��̹Ƿ�, ��ü �ν��Ͻ� ���� ȣ�� 

	constexpr DeleteFunc Delete = &CEventManager::DeleteGameObject; //��� �Լ� ������ - constexpr�� �ٿ����Ƿ� ������ Ÿ�� ����� ���
}

