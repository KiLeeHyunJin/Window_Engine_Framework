#include "CTimeManager.h"

namespace Framework
{
	LARGE_INTEGER	CTimeManager::m_liCpuFrequency		= {};
	LARGE_INTEGER	CTimeManager::m_liPrevFrequency		= {};
	LARGE_INTEGER	CTimeManager::m_liCurrentFrequency	= {};

	ULONGLONG		CTimeManager::m_fDeltaTick			= 0;
	ULONGLONG		CTimeManager::m_fPrevTick			= 0;

	float			CTimeManager::m_fDeltaTime			= 0;

	std::chrono::high_resolution_clock::time_point CTimeManager::curTime	= {};
	std::chrono::high_resolution_clock::time_point CTimeManager::prevTime	= {};

	CTimeManager::CTimeManager()		{	}
	
	CTimeManager::~CTimeManager()		{	}

	void CTimeManager::Initialize()
	{
		QueryPerformanceFrequency(&m_liCpuFrequency);
		QueryPerformanceCounter(&m_liPrevFrequency);
	}

	void CTimeManager::Tick()
	{

		// //Performance Time //CPU 클럭 주파수를 기반, 정확도 - 매우 높음, 일관성 - 일부 멀티 코어 환경에서 문제 발생 가능
		//{
		//	QueryPerformanceCounter(&m_liCurrentFrequency);
		//	float dirrentFrequency = static_cast<float>(m_liCurrentFrequency.QuadPart - m_liPrevFrequency.QuadPart);

		//	m_fDeltaTime = dirrentFrequency / static_cast<float>(m_liCpuFrequency.QuadPart);

		//	m_liPrevFrequency.QuadPart = m_liCurrentFrequency.QuadPart;
		//}
		// //Tick Time //OS 타이머 기반 정확도 - 낮음, 
		//{
		//	const ULONGLONG currentTick = GetTickCount64();
		//	m_fDeltaTick = currentTick - m_fPrevTick;
		//	m_fPrevTick = currentTick;
		//}
		
		
		//Chrono Time //C++11 이후 표준 라이브러리 정확도 ㅔ 매우 높음, 일관성 - 운영체제에 종속되어 있는 않는 기능(독립적)
		{
			curTime = std::chrono::high_resolution_clock::now();

			std::chrono::duration<float> elapsed = curTime - prevTime; // 이전 프레임이랑 차이 시간 계산
			m_fDeltaTime = std::clamp(elapsed.count(), 0.0f, 0.1f);

			prevTime = curTime;
			//지연에 의한 순간이동 현상을 억제
			if (m_fDeltaTime > 0.1f)
			{
				m_fDeltaTime = 0.1f;
			}
		}
	}

	void CTimeManager::Render(HDC hdc)
	{
		//static float time = 0;
		
		//time += m_fDeltaTime;
		float fps = 1.0f / m_fDeltaTime;

		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"FPS : %d", (int)fps);
		int len = (int)wcsnlen_s(str, 50);

		TextOut(hdc, 0, 0, str, len);
	}


}