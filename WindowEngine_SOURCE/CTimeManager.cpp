#include "CTimeManager.h"
#include "CApplication.h"

namespace Framework
{

	namespace Manager
	{
		CTimeManager* CTimeManager::s_instance = nullptr;

		CTimeManager::~CTimeManager() {}

		void CTimeManager::Initialize()
		{
			const LONGLONG seedNum = reinterpret_cast<LONGLONG>(this);
			generator_.seed(static_cast<UINT>(seedNum));

			QueryPerformanceFrequency(&m_liCpuFrequency);
			QueryPerformanceCounter(&m_liPrevFrequency);

			functions[(int)eTimeType::Tick]			= &CTimeManager::TimeTick;
			functions[(int)eTimeType::Performance]	= &CTimeManager::TimePerformance;
			//functions[(int)eTimeType::Chrono]		= CTimeManager::TimeChrono;
		}

		void CTimeManager::Tick()
		{
			//델타 타임 계산
			(this->*functions[(UINT)m_eTimeType])();
			//TimePerformance();
			//지연에 의한 순간이동 현상을 억제
			if (m_fDeltaTime > 0.1f)
			{
				m_fDeltaTime = 0.1f;
			}

#pragma region FPS

			static float stackDeltaTime = 0;
			static UINT TickCount = 0;

			stackDeltaTime += m_fDeltaTime;

			if (stackDeltaTime >= 1.0f)
			{
				m_uiFPS = TickCount;
				stackDeltaTime = 0;
				TickCount = 1;
			}
			else
			{
				TickCount += 1;
			}
#pragma endregion
		}

		void CTimeManager::Render(HDC hdc) const
		{
			return;
		}

		/// <summary>
		/// OS 타이머 기반
		/// </summary>
		void CTimeManager::TimeTick()
		{
			static ULONGLONG m_fPrevTick = 0;

			const  ULONGLONG currentTick = GetTickCount64();
			const  ULONGLONG m_fDeltaTick = currentTick - m_fPrevTick;
			m_fPrevTick = currentTick;

			m_fDeltaTime = m_fDeltaTick * 0.001f;
		}

		/// <summary>
		/// CPU 클럭 주파수를 기반
		/// </summary>
		void CTimeManager::TimePerformance()
		{
			LARGE_INTEGER	m_liCurrentFrequency = {};
			QueryPerformanceCounter(&m_liCurrentFrequency);

			float dirrentFrequency = static_cast<float>(m_liCurrentFrequency.QuadPart - m_liPrevFrequency.QuadPart);
			m_fDeltaTime = dirrentFrequency / static_cast<float>(m_liCpuFrequency.QuadPart);

			m_liPrevFrequency.QuadPart = m_liCurrentFrequency.QuadPart;
		}


		/// <summary>
		/// C++17 이후 표준 라이브러리
		/// </summary>
		/*
		void CTimeManager::TimeChrono()
		{
			static std::chrono::high_resolution_clock::time_point curTime	= {};
			static std::chrono::high_resolution_clock::time_point prevTime	= {};

			curTime = std::chrono::high_resolution_clock::now();

			const std::chrono::duration<float> elapsed = curTime - prevTime;
			prevTime = curTime;

			m_fDeltaTime = std::clamp(elapsed.count(), 0.0f, 0.1f);
		}
		*/

	}


}