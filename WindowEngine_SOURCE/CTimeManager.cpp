#include "CTimeManager.h"

namespace Framework
{
	float			CTimeManager::m_fDeltaTime			= 0;
	UINT			CTimeManager::m_uiFPS				= 0;
	CTimeManager::eTimeType CTimeManager::timeType		= CTimeManager::eTimeType::Chrono;
	CTimeManager::FunctionPtr CTimeManager::functions[3]= { nullptr};

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
		
		//������ ���� �����̵� ������ ����
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
	/// OS Ÿ�̸� ��� ��Ȯ�� - ����, 
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
	/// CPU Ŭ�� ���ļ��� ���, ��Ȯ�� - �ſ� ����, �ϰ��� - �Ϻ� ��Ƽ �ھ� ȯ�濡�� ���� �߻� ����
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
	/// C++11 ���� ǥ�� ���̺귯�� ��Ȯ�� - �ſ� ����, �ϰ��� - �ü���� ���ӵǾ� �ִ� �ʴ� ���(������)
	/// </summary>
	void CTimeManager::TimeChrono()
	{
		static std::chrono::high_resolution_clock::time_point curTime	= {};
		static std::chrono::high_resolution_clock::time_point prevTime	= {};

		curTime = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> elapsed = curTime - prevTime; // ���� �������̶� ���� �ð� ���
		prevTime = curTime;

		m_fDeltaTime = std::clamp(elapsed.count(), 0.0f, 0.1f);
	}


}