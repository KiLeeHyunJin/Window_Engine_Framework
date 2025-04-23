#pragma once
#include "CommonInclude.h"
#include "CSoundManager.h"

namespace Framework
{
	namespace Resource
	{
		class CSound;
	}

	class CSoundChannel
	{
	public:
		CSoundChannel();
		virtual ~CSoundChannel();

		void Initialize(UINT channelNum, FMOD::ChannelGroup* masterGroup);
		void SetGroup(SOUND::eSoundGroup group);
		void Release();

		void GetVolume(float* fVolume)			{ m_pChannel->getVolume(fVolume); }
		void GetPitch(float* fPitch)			{ m_pChannel->getPitch(fPitch); }
		void GetMute(bool* bMute)				{ m_pChannel->getMute(bMute); }
		void GetPaused(bool* paused)			{ m_pChannel->getPaused(paused); }

		void SetVolume(float fVolume)		{ m_pChannel->setVolume(fVolume); }
		void SetPitch(float fPitch)			{ m_pChannel->setPitch(fPitch); }
		void SetMute(bool state)			{ m_pChannel->setMute(state); }
		void SetPaused(bool paused)			{ m_pChannel->setPaused(paused); }

		void SetSoundClip(const Resource::CSound* pSound,bool bLoop);


		void GetDelay(ULONG64* fStart, ULONG64* fEnd, bool* stopChannels)		{ m_pChannel->getDelay(fStart, fEnd, stopChannels); }
		void SetDelay(ULONG64 fStart, ULONG64 fEnd, bool stopChannels = true)	{ m_pChannel->setDelay(fStart, fEnd, stopChannels); }
	private:
		FMOD::Channel* m_pChannel	= nullptr;
		FMOD::ChannelGroup* m_pGroup = nullptr;

		UINT m_uiChannel = 0;
	};

}


