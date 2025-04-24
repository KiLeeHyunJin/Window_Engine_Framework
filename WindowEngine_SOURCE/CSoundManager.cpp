#include "CSoundManager.h"
#include "CSound.h"
#include "CSoundChannel.h"



namespace Framework
{
	namespace Manager
	{
		CSoundManager* CSoundManager::s_instance = nullptr;
		using namespace FMOD;

		void CSoundManager::Initialize()
		{
			FMOD::System_Create(&m_pSystem);
			assert(m_pSystem);
			m_pSystem->init(SOUND_MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);

			CreateGroup();
		}

		void CSoundManager::Release()
		{
			for (auto& pChannel : m_vecChannels)
			{
				pChannel->Release();
				delete pChannel;
			}
			m_vecChannels.clear();
			m_vecGroups.clear();

			m_pSystem->close();
			m_pSystem->release();

			m_vecDspCompressor.clear();
			m_vecDspHighpass.clear();
			m_vecDspLowpass.clear();

			m_pSystem = nullptr;
			m_pMasterGroup = nullptr;
		}

		void CSoundManager::Tick()
		{
			m_pSystem->update();
		}

		CSoundChannel* CSoundManager::SetSoundClip(const Resource::CSound* pSound, bool bLoop)
		{
			const UINT channelNum = pSound->GetChannel();
			CSoundChannel* pChannel = m_vecChannels[channelNum];
			pChannel->SetSoundClip(pSound, bLoop);
			return pChannel;
		}

		void CSoundManager::CreateGroup()
		{
			m_pSystem->getMasterChannelGroup(&m_pMasterGroup);

			m_vecChannels.resize(SOUND_MAX_CHANNEL);
			for (UINT i = 0; i < m_vecChannels.size(); i++)
			{
				m_vecChannels[i] = new CSoundChannel();
				m_vecChannels[i]->Initialize(i, m_pMasterGroup);
			}

			m_vecGroups			.resize((UINT)eSoundGroup::Size);
			m_vecDspLowpass		.resize((UINT)eSoundGroup::Size);
			m_vecDspHighpass	.resize((UINT)eSoundGroup::Size);
			m_vecDspCompressor	.resize((UINT)eSoundGroup::Size);

			m_pSystem->createChannelGroup("Background"	, &m_vecGroups[(UINT)eSoundGroup::Background]);
			m_pSystem->createChannelGroup("Effect"		, &m_vecGroups[(UINT)eSoundGroup::Effect]);
			m_pSystem->createChannelGroup("UI"			, &m_vecGroups[(UINT)eSoundGroup::UI]);
			m_pSystem->createChannelGroup("Voice"		, &m_vecGroups[(UINT)eSoundGroup::Voice]);

			for (size_t i = 0; i < m_vecGroups.size(); i++)
			{
				m_pSystem->createDSPByType(FMOD_DSP_TYPE_LOWPASS,		&m_vecDspLowpass[i]);
				m_pSystem->createDSPByType(FMOD_DSP_TYPE_HIGHPASS,		&m_vecDspHighpass[i]);
				m_pSystem->createDSPByType(FMOD_DSP_TYPE_COMPRESSOR,	&m_vecDspCompressor[i]);

				m_vecGroups[i]->addDSP(0, m_vecDspCompressor[i]); // 입력에 가까이
				m_vecGroups[i]->addDSP(1, m_vecDspLowpass[i]);
				m_vecGroups[i]->addDSP(2, m_vecDspHighpass[i]);   // 출력에 가까이

				m_vecDspLowpass[i]->setBypass(true);
				m_vecDspHighpass[i]->setBypass(true);
				m_vecDspCompressor[i]->setBypass(true);
			}

			for (auto group : m_vecGroups)
			{
				m_pMasterGroup->addGroup(group);	
			}

		}

		bool CSoundManager::GetHighPass(eSoundGroup eGroup) const
		{
			bool bypass;
			m_vecDspHighpass[(UINT)eGroup]->getBypass(&bypass);
			return bypass;
		}

		bool CSoundManager::GetLowPass(eSoundGroup eGroup) const
		{
			bool bypass;
			m_vecDspLowpass[(UINT)eGroup]->getBypass(&bypass);
			return bypass;
		}

		void CSoundManager::SetGroup(std::vector<eSoundGroup>& channelGroups)
		{
			for (size_t i = 0; i < channelGroups.size(); i++)
			{
				m_vecChannels[i]->SetGroup(channelGroups[i]);
			}
		}

		void CSoundManager::ResetPass(eSoundGroup eGroup)
		{
			if (GetHighPass(eGroup) == false)
			{
				SetHighPass(eGroup, true);
			}
			if (GetLowPass(eGroup) == false)
			{
				SetLowPass(eGroup, true);
			}
		}

	}
}