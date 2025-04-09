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
			DECLARE_SINGLE(CTimeManager)
			RELEASE_SINGLE
		public:
			enum class eTimeType
			{
				Tick,
				Performance,
				//Chrono,
				Size
			};

			__forceinline void SetTimeType(eTimeType type)	{ timeType = type;						}
			__forceinline float DeltaTime() const			{ return m_fDeltaTime * m_fTimeScale;	}
			__forceinline float RealDeltaTime() const		{ return m_fDeltaTime;					}
			__forceinline UINT FPS() const					{ return m_uiFPS;						}
			__forceinline void SetShowFPS(bool state)		{ m_bShowFPS = state;					}
			__forceinline bool GetShowFPS() const			{ return m_bShowFPS;					}
			__forceinline float GetTimeScale() const		{ return m_fTimeScale;					}
			__forceinline void SetTimeScale(float scale)	{ m_fTimeScale = scale;					}
			//__forceinline ULONGLONG TickTime()					{ return m_fDeltaTime; }

			friend class CApplication;
			friend CRenderManager;
		private:
			//CTimeManager();
			~CTimeManager();

			void Initialize();
			void Tick();
			void Render(HDC hdc);

			void TimeTick();
			void TimePerformance();
			void Release() {}
			//void TimeChrono();

			float m_fDeltaTime											= {};
			float m_fTimeScale											= {};
			bool m_bShowFPS												= {};
			UINT m_uiFPS												= {};
			eTimeType timeType											= {};

			using TimeFuncPtr = void (*)();
			TimeFuncPtr functions[static_cast<int>(eTimeType::Size)]	= {};

			/// CPU Preformance
			LARGE_INTEGER m_liCpuFrequency								= {};
			LARGE_INTEGER m_liPrevFrequency								= {};
		};
	}
	using TIME = Manager::CTimeManager;

#define DELTATIME Manager::CTimeManager::DeltaTime()
#define FPS Manager::CTimeManager::FPS()
}



