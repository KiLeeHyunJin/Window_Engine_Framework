#include "CFlipbookActor.h"
#include "CFlipbook.h"
#include "CSprite.h"
#include "CTimeManager.h"
#include "Utils.h"
namespace Framework
{
	CFlipbookActor::CFlipbookActor(UINT layer) :CActor(layer), m_fSumTime(0), m_pFlipbook(nullptr), m_uiIndex(0), m_bCompleted(false)
	{
	}
	CFlipbookActor::~CFlipbookActor()
	{
	}
	void CFlipbookActor::Reset()
	{
		m_uiIndex = 0;
		m_bCompleted = false;
	}
	void CFlipbookActor::BeginPlay()
	{
		SUPER::BeginPlay();
	}
	void CFlipbookActor::Release()
	{
		SUPER::Release();
	}
	bool CFlipbookActor::Tick()
	{
		SUPER::Tick();
		AnimationTick();
	
		return true;
	}
	bool CFlipbookActor::LastTick()
	{
		return SUPER::LastTick();
	}
	void CFlipbookActor::Render(HDC hdc) const
	{
		SUPER::Render(hdc);
		if (m_pFlipbook == nullptr)
		{
			return;
		}
		const Maths::Vector2& position = GetPosition();
		const Maths::Vector2& scale = GetScale();

		const auto& pair = m_pFlipbook->GetPair(m_uiIndex);
		const CSprite* sprite = pair.first;

		const Maths::Vector2Int& spriteSize = sprite->GetSize();
		const Maths::Vector2Int& spriteLeftTop = sprite->GetLeftTop();
		HDC spriteHdc = sprite->GetHDC();

		Utils::UtilBitBlt(hdc, position, spriteSize, sprite);

	}


	void CFlipbookActor::AnimationTick()
	{
		if (m_pFlipbook == nullptr)
		{
			return;
		}
		const INT animSize = m_pFlipbook->GetSize();
		const bool loop = m_pFlipbook->GetLoop();

		if (m_bCompleted && loop == false)
		{
			return;
		}
		else
		{
			m_fSumTime += CTimeManager::DeltaTime();
			const auto& pair = m_pFlipbook->GetPair(m_uiIndex);

			const float duration = pair.second;
			if (duration <= m_fSumTime)
			{
				m_fSumTime = 0;
				m_uiIndex++;
				if (animSize < m_uiIndex)
				{
					m_bCompleted = true;
					if (loop)
					{
						m_uiIndex = 0;
					}
					else
					{
						m_uiIndex = animSize;
					}
				}
			}
		}
		

	}
}