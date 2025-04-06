#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	class CRenderManager;

	class CObjectManager
	{
	public:

		friend CApplication;
		friend CRenderManager;
	private:
		static void Initialize();
		static void Release();

		static void Tick();
		static void LastTick();
		static void Render(HDC hdc);
	};
	using OBJECT = CObjectManager;

}

