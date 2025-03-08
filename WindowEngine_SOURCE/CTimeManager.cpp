#include "CTimeManager.h"

namespace Framework
{
	float			CTimeManager::m_fDeltaTime			= 0;
	UINT			CTimeManager::m_uiFPS				= 0;
	CTimeManager::eTimeType CTimeManager::timeType		= CTimeManager::eTimeType::Chrono;
	VoidPtr			CTimeManager::functions[3]= { nullptr};

	LARGE_INTEGER	CTimeManager::m_liCpuFrequency		= {};
	LARGE_INTEGER	CTimeManager::m_liPrevFrequency		= {};

	CTimeManager::CTimeManager()		{	}
	
	CTimeManager::~CTimeManager()		{	}

	void CTimeManager::Initialize()
	{
		QueryPerformanceFrequency(&m_liCpuFrequency);
		QueryPerformanceCounter(&m_liPrevFrequency);

		functions[(int)eTimeType::Tick]			= CTimeManager::TimeTick;
		functions[(int)eTimeType::Performance]	= CTimeManager::TimePerformance;
		functions[(int)eTimeType::Chrono]		= CTimeManager::TimeChrono;
	}

	void CTimeManager::Tick()
	{
		functions[(UINT)timeType]();
		
		//지연에 의한 순간이동 현상을 억제
		if (m_fDeltaTime > 0.1f)
		{
			m_fDeltaTime = 0.1f;
		}
#pragma region FPS

		static float stackDeltaTime = 0;
		static UINT tickCount = 0;

		stackDeltaTime += m_fDeltaTime;

		if (stackDeltaTime >= 1.0f)
		{
			m_uiFPS = tickCount;
			stackDeltaTime = 0;
			tickCount = 1;
		}
		else
		{
			tickCount += 1;
		}
#pragma endregion
	}

	void CTimeManager::Render(HDC hdc)
	{
		//static float time = 0;
		
		//time += m_fDeltaTime;
		//float fps = 1.0f / m_fDeltaTime;

		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"FPS : %d", (int)m_uiFPS);
		int len = (int)wcsnlen_s(str, 50);

		TextOut(hdc, 0, 0, str, len);
	}

	/// <summary>
	/// OS 타이머 기반 정확도 - 낮음, 
	/// </summary>
	void CTimeManager::TimeTick()
	{
		static ULONGLONG m_fDeltaTick	= 0;
		static ULONGLONG m_fPrevTick	= 0;
		const  ULONGLONG currentTick	= GetTickCount64();

		m_fDeltaTick = currentTick - m_fPrevTick;
		m_fDeltaTime = m_fDeltaTick * 0.001f;
		m_fPrevTick = currentTick;
	}

	/// <summary>
	/// CPU 클럭 주파수를 기반, 정확도 - 매우 높음, 일관성 - 일부 멀티 코어 환경에서 문제 발생 가능
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
	/// C++11 이후 표준 라이브러리 정확도 - 매우 높음, 일관성 - 운영체제에 종속되어 있는 않는 기능(독립적)
	/// </summary>
	void CTimeManager::TimeChrono()
	{
		static std::chrono::high_resolution_clock::time_point curTime	= {};
		static std::chrono::high_resolution_clock::time_point prevTime	= {};

		curTime = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> elapsed = curTime - prevTime; // 이전 프레임이랑 차이 시간 계산
		prevTime = curTime;

		m_fDeltaTime = std::clamp(elapsed.count(), 0.0f, 0.1f);
	}


}