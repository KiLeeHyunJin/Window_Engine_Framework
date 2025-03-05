#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	class CRenderManager;

	class CTimeManager
	{
	public:
		CTimeManager();
		virtual ~CTimeManager();

		__forceinline static float DeltaTime()		{ return m_fDeltaTime; }
		__forceinline static float FPS()			{ return m_uiFPS; }
		__forceinline static ULONGLONG TickTime()	{ return m_fDeltaTick; }

		friend CApplication;
		friend CRenderManager;
	private:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static float m_fDeltaTime;
		static UINT m_uiFPS;

		/// CPU Preformance
		static LARGE_INTEGER m_liCpuFrequency;
		static LARGE_INTEGER m_liPrevFrequency;
		static LARGE_INTEGER m_liCurrentFrequency;

		/// Chrono Time
		static std::chrono::high_resolution_clock::time_point curTime;
		static std::chrono::high_resolution_clock::time_point prevTime;

		///OS Tick Count
		static ULONGLONG m_fPrevTick;
		static ULONGLONG m_fDeltaTick;
	};
	using TIME = CTimeManager;
//#define TIME CTimeManager
//using DELTATIME = CTimeManager::DeltaTime();
#define DELTATIME CTimeManager::DeltaTime()
#define FPS CTimeManager::FPS()
}



