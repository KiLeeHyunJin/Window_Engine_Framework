#include "CAnimation.h"
#include "CTimeManager.h"


namespace Framework
{

	Resource::CAnimation::CAnimation() :
		CResource(Enums::eResourceType::Animation),
		m_pOwner(nullptr), m_pTexture(nullptr), m_vecSprites{},
		m_iIndex(-1), m_fTime(0), m_bLoop(false), m_bCompleted(false)
	{
	}

	Resource::CAnimation::~CAnimation()
	{
	}

	HRESULT Resource::CAnimation::Load(const std::wstring& wstrPath)
	{
		return E_NOTIMPL;
	}

	void Resource::CAnimation::Reset()
	{
		m_fTime = 0.0f;
		m_iIndex = 0;
		m_bCompleted = false;

	}

	void Resource::CAnimation::Tick()
	{
		if (m_bCompleted)
		{
			return;
		}
		m_fTime += DELTATIME;
		if (m_vecSprites[m_iIndex].duration < m_fTime)
		{
			if (m_iIndex < m_vecSprites.size() - 1)
			{
				m_iIndex++;
			}
			else
			{
				if (m_bCompleted == false)
				{
					m_bCompleted = true;
				}
			}
		}
	}

	void Resource::CAnimation::Render(HDC hdc)
	{
	}

	void Resource::CAnimation::CreateAnimation(const std::wstring& name, Resource::CTexture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
	}


}

