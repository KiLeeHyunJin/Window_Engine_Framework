#pragma once
#include "CommonInclude.h"

namespace Framework
{
	class CSoundChannel
	{
	public:
		void Initialize(UINT channelNum, FMOD::System* pSystem);
		void Release();
		void Tick();

		void GetVolume(float* fVolume)			{ m_pChannelGroup->getVolume(fVolume); }
		void GetPitch(float* fPitch)			{ m_pChannelGroup->getPitch(fPitch); }
		void GetMute(bool* bMute)				{ m_pChannelGroup->getMute(bMute); }
		void GetPaused(bool* paused)			{ m_pChannelGroup->getPaused(paused); }

		void SetVolume(float fVolume)		{ m_pChannelGroup->setVolume(fVolume); }
		void SetPitch(float fPitch)			{ m_pChannelGroup->setPitch(fPitch); }
		void SetMute(bool state)			{ m_pChannelGroup->setMute(state); }
		void SetPaused(bool paused)			{ m_pChannelGroup->setPaused(paused); }


		void GetDelay(ULONG64* fStart, ULONG64* fEnd, bool* stopChannels)		{ m_pChannelGroup->getDelay(fStart, fEnd, stopChannels); }
		void SetDelay(ULONG64 fStart, ULONG64 fEnd, bool stopChannels = true)	{ m_pChannelGroup->setDelay(fStart, fEnd, stopChannels); }
	private:
		FMOD::ChannelGroup* m_pChannelGroup;
	};

}


