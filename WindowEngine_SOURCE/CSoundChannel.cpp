#include "CSoundChannel.h"
#include <sstream>

namespace Framework
{
	void CSoundChannel::Initialize(UINT channelNum, FMOD::System* pSystem)
	{
		std::stringstream ss = {};

		ss << "Group " << channelNum;
		std::string result = ss.str();
		pSystem->createChannelGroup(result.c_str(), &m_pChannelGroup);
	}

	void CSoundChannel::Release()
	{
		m_pChannelGroup->release();
	}

	void CSoundChannel::Tick()
	{
	}
}