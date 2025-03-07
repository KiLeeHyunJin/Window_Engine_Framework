#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CApplication;
	class CRenderManager;

	class CTimeManager
	{
	public:
		enum class eTimeType
		{
			Tick,
			Performance,
			Chrono
		};
		CTimeManager();
		virtual ~CTimeManager();

		__forceinline static void SetTimeType(eTimeType type)		{ timeType = type; }
		__forceinline static float DeltaTime()						{ return m_fDeltaTime; }
		__forceinline static UINT FPS()								{ return m_uiFPS; }
		//__forceinline static ULONGLONG TickTime()					{ return m_fDeltaTime; }

		friend CApplication;
		friend CRenderManager;
	private:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static void TimeTick();
		static void TimePerformance();
		static void TimeChrono();

		static float m_fDeltaTime;
		static UINT m_uiFPS;
		static eTimeType timeType;

		static VoidPtr functions[3];

		/// CPU Preformance
		static LARGE_INTEGER m_liCpuFrequency;
		static LARGE_INTEGER m_liPrevFrequency;
	};

	using TIME = CTimeManager;

#define DELTATIME CTimeManager::DeltaTime()
#define FPS CTimeManager::FPS()
}



