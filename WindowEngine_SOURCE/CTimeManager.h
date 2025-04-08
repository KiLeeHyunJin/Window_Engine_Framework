#pragma once
#include "CommonInclude.h"

namespace Framework
{
	//class CApplication;

	namespace Manager
	{
		class CRenderManager;

		class CTimeManager
		{
		public:
			enum class eTimeType
			{
				Tick,
				Performance,
				//Chrono,
				Size
			};

			__forceinline static void SetTimeType(eTimeType type) { timeType = type; }
			__forceinline static float DeltaTime() { return m_fDeltaTime * m_fTimeScale; }
			__forceinline static float RealDeltaTime() { return m_fDeltaTime; }
			__forceinline static UINT FPS() { return m_uiFPS; }
			__forceinline static void SetShowFPS(bool state) { m_bShowFPS = state; }
			__forceinline static bool GetShowFPS() { return m_bShowFPS; }
			__forceinline static float GetTimeScale() { return m_fTimeScale; }
			__forceinline static void SetTimeScale(float scale) { m_fTimeScale = scale; }
			//__forceinline static ULONGLONG TickTime()					{ return m_fDeltaTime; }

			friend class CApplication;
			friend CRenderManager;
		private:
			CTimeManager();
			~CTimeManager();

			static void Initialize();
			static void Tick();
			static void Render(HDC hdc);

			static void TimeTick();
			static void TimePerformance();
			//static void TimeChrono();

			static float m_fDeltaTime;
			static float m_fTimeScale;
			static bool m_bShowFPS;
			static UINT m_uiFPS;
			static eTimeType timeType;

			using TimeFuncPtr = void (*)();
			static TimeFuncPtr functions[static_cast<int>(eTimeType::Size)];

			/// CPU Preformance
			static LARGE_INTEGER m_liCpuFrequency;
			static LARGE_INTEGER m_liPrevFrequency;
		};
	}
	using TIME = Manager::CTimeManager;

#define DELTATIME Manager::CTimeManager::DeltaTime()
#define FPS Manager::CTimeManager::FPS()
}



