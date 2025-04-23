#include "CSoundChannel.h"
#include <sstream>
#include "CSound.h"
#include "Utils.h"
namespace Framework
{
	CSoundChannel::CSoundChannel()
	{
	}
	CSoundChannel::~CSoundChannel()
	{
	}
	void CSoundChannel::Initialize(UINT channelNum, FMOD::ChannelGroup* masterGroup)
	{
		m_uiChannel = channelNum;
		std::stringstream ss = {};

		ss << "Group " << channelNum;
		std::string result = ss.str();
		m_pChannel->setChannelGroup(masterGroup);
	}

	void CSoundChannel::SetGroup(SOUND::eSoundGroup group)
	{
		m_pGroup = GET_SINGLE(SOUND).GetGroup(group);
	}

	void CSoundChannel::SetSoundClip(const Resource::CSound* pSound, bool bLoop)
	{
		FMOD_MODE mode = bLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

		FMOD::Sound* sound = pSound->GetSound();
		sound->setMode(mode);

		GET_SINGLE(SOUND).GetSystem()->playSound(sound, m_pGroup, false, &m_pChannel);
	}


	void CSoundChannel::Release()
	{
	}



}