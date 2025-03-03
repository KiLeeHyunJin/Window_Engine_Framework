#include "CTimeManager.h"

namespace Framework
{
	LARGE_INTEGER	CTimeManager::m_liCpuFrequency		= {};
	LARGE_INTEGER	CTimeManager::m_liPrevFrequency		= {};
	LARGE_INTEGER	CTimeManager::m_liCurrentFrequency	= {};

	ULONGLONG		CTimeManager::m_fDeltaTick			= 0;
	ULONGLONG		CTimeManager::m_fPrevTick			= 0;

	float			CTimeManager::m_fDeltaTime			= 0;

	CTimeManager::CTimeManager()		{	}
	
	CTimeManager::~CTimeManager()		{	}

	void CTimeManager::Initialize()
	{
		QueryPerformanceFrequency(&m_liCpuFrequency);
		QueryPerformanceCounter(&m_liPrevFrequency);
	}

	void CTimeManager::Tick()
	{
		QueryPerformanceCounter(&m_liCurrentFrequency);
		float dirrentFrequency = static_cast<float>(m_liCurrentFrequency.QuadPart - m_liPrevFrequency.QuadPart);
		
		m_fDeltaTime = dirrentFrequency / static_cast<float>(m_liCpuFrequency.QuadPart);

		m_liPrevFrequency.QuadPart = m_liCurrentFrequency.QuadPart;

		const ULONGLONG currentTick = GetTickCount64();
		m_fDeltaTick = currentTick - m_fPrevTick;
		m_fPrevTick = currentTick;
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