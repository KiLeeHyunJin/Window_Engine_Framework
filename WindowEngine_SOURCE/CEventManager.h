#pragma once
#include "CommonInclude.h"


namespace Framework
{
	class CApplication;

	class CEventManager
	{
	public:


		friend CApplication;
	private:
		CEventManager();
		~CEventManager();


	};
	using Event = CEventManager;
}

