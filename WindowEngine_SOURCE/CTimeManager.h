#pragma once
#include "CommonInclude.h"

#include <random>

namespace Framework
{
	//class CApplication;

	namespace Manager
	{
		class CRenderManager;

		class CTimeManager 
		{
			DECLARE_SINGLE(CTimeManager)
			RELEASE_SINGLE(CTimeManager)
		public:
			enum class eTimeType
			{
				Tick,
				Performance,
				//Chrono,
				Size
			};

			__forceinline float		ApplicationDeltaTime()	const	{ return m_fDeltaTime; }
			__forceinline float		DeltaTime()				const	{ return DELTA_TICK * m_fTimeScale;		}
			__forceinline float		RealDeltaTime()			const	{ return DELTA_TICK;						}
			float					GetTimeScale()			const	{ return m_fTimeScale;						}

			UINT					FPS()					const	{ return m_uiFPS;							}
			bool					GetShowFPS()			const	{ return m_bShowFPS;						}
			UINT32					GetRandom()						{ return GetRandomInRange(1, UINT32_MAX);	}

			// 사용자 지정 범위
			__forceinline UINT32	GetRandomInRange(UINT32 min, UINT32 max)
			{
				std::uniform_int_distribution<UINT32> dist(min, max);
				return dist(generator_);
			}

			void					SetTimeScale(float scale)		{ m_fTimeScale = scale; }
			void					SetShowFPS(bool state)			{ m_bShowFPS = state; }
			void					SetTimeType(eTimeType type)		{ m_eTimeType = type; }

			
			void Render(HDC hdc) const;

			friend class CApplication;
			//friend CRenderManager;
		private:
			//CTimeManager();
			~CTimeManager();

			void Initialize();
			void Tick();

			void TimeTick();
			void TimePerformance();
			void Release() {}
			//void TimeChrono();

			float m_fDeltaTime											= 0;
			float m_fTimeScale											= 1;
			bool m_bShowFPS												= 0;
			UINT m_uiFPS												= 0;
			eTimeType m_eTimeType										= eTimeType::Performance;

			using TimeFuncPtr = void (CTimeManager::*)();
			TimeFuncPtr functions[static_cast<int>(eTimeType::Size)]	= {};

			/// CPU Preformance
			LARGE_INTEGER m_liCpuFrequency								= {};
			LARGE_INTEGER m_liPrevFrequency								= {};

			std::mt19937 generator_ = {};

		};
	}
	using TIME = Manager::CTimeManager;

#define DELTATIME Manager::CTimeManager::DeltaTime()
#define FPS Manager::CTimeManager::FPS()
}



