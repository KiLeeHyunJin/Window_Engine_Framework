#include "CPlayerControllActor.h"
#include "CInputManager.h"
#include "CSoundManager.h"
#include "CResourceManager.h"

#include "CSoundChannel.h"
#include "CSound.h"

#include "CRigidbodyComponent.h"
#include "CColliderComponent.h"

namespace Framework
{
	CPlayerControllActor::CPlayerControllActor(UINT layer) :CActor(layer)
	{
	}
	void CPlayerControllActor::BeginPlay()
	{
		SUPER::BeginPlay();
	}
	void CPlayerControllActor::Release()
	{
		SUPER::Release();
	}
	bool CPlayerControllActor::Tick()
	{
		SUPER::Tick();
		const float speed = 20;
		//const float TickComponentTime = GET_SINGLE(TIME).DeltaTime();
		const float movePower = speed * 5;
		CRigidbodyComponent* rigid = GetComponent<CRigidbodyComponent>();
		if (rigid == nullptr)
		{		return true;		}
		Maths::Vector2 addForceDir;

		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::Left))
		{
			addForceDir += Maths::Vector2::Left;
		}
		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::Right))
		{
			addForceDir += Maths::Vector2::Right;
		}


		if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::Up))
		{
			bool state = GET_SINGLE(SOUND).GetLowPass(SOUND::eSoundGroup::Effect);
			GET_SINGLE(SOUND).SetLowPass(SOUND::eSoundGroup::Effect, !state);
		}
		
		if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::Down))
		{
			bool state = GET_SINGLE(SOUND).GetHighPass(SOUND::eSoundGroup::Effect);
			GET_SINGLE(SOUND).SetHighPass(SOUND::eSoundGroup::Effect, !state);
		}

		if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::Space))
		{
			const Resource::CSound* pSound = GET_SINGLE(RESOURCE).FindSound(L"sound2");
			GET_SINGLE(SOUND).SetSoundClip(pSound);
			GET_SINGLE(SOUND).GetChannel(pSound->GetChannel())->SetVolume(1);
		}

		else if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::Left))
		{
			//const Resource::CSound* pSound = GET_SINGLE(RESOURCE).FindSound(L"sound2");
			//CSoundChannel* channel = GET_SINGLE(SOUND).GetChannel(pSound->GetChannel());
			//GET_SINGLE(SOUND).ResetPass(SOUND::eSoundGroup::Effect);

			const Resource::CSound* pSound = GET_SINGLE(RESOURCE).FindSound(L"sound2");
			CSoundChannel* pChannel =  GET_SINGLE(SOUND).GetChannel((UINT)SOUND::eSoundGroup::Background);
			pChannel->SetSoundClip(pSound, false);
		}

		if (addForceDir.HasValue())
		{
			addForceDir.Normalize();
			rigid->SetVelocity(addForceDir * movePower);
		}
		return true;
	}
	bool CPlayerControllActor::LastTick()
	{
		SUPER::LastTick();

		return true;
	}

	void CPlayerControllActor::FixedTick()
	{
	}
	void CPlayerControllActor::Render(HDC hdc) const
	{

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc,transparentBrush);
		
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(m_color.r, m_color.g, m_color.b));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		transparentBrush = (HBRUSH)SelectObject(hdc, oldBrush);

		SUPER::Render(hdc);

		pen = (HPEN)SelectObject(hdc, oldPen);

		DeleteObject(pen);

	}
	void CPlayerControllActor::OnCollisionEnter(CColliderComponent* other)
	{
		collChecking = other->GetColliderID();
		m_color.r = 255;
		m_color.g = 0;
		m_color.b = 0;
	}
	void CPlayerControllActor::OnCollisionStay(CColliderComponent* other)
	{
	}
	void CPlayerControllActor::OnCollisionExit(CColliderComponent* other)
	{
		collChecking = UINT32_MAX;
		m_color.r = 0;
		m_color.g = 0;
		m_color.b = 255;
	}

}