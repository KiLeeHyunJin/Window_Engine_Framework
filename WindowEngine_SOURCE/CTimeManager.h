#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;

	class CTimeManager
	{
	public:
		CTimeManager();
		virtual ~CTimeManager();

		static float DeltaTime() { return m_fDeltaTime; }

		friend CApplication;
	private:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static LARGE_INTEGER m_liCpuFrequency;
		static LARGE_INTEGER m_liPrevFrequency;
		static LARGE_INTEGER m_liCurrentFrequency;
		static float m_fDeltaTime;
	};

#define TIME CTimeManager
#define DELTATIME CTimeManager::DeltaTime()
}



