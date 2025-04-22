#include "CSoundManager.h"
#include "CSound.h"



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
			m_pSystem->release();
			m_pSystem->close();
		}

		void CSoundManager::Tick()
		{
			m_pSystem->update();
		}

		void CSoundManager::PlaySound(Resource::CSound* pSound, UINT iChannel, float fVolume)
		{

		}

		void CSoundManager::PlayBGM(Resource::CSound* pSound, float fVolume)
		{
		}

		void CSoundManager::StopSound(UINT eID)
		{
		}

		void CSoundManager::StopAll()
		{
		}


		void CSoundManager::CreateGroup()
		{
			m_pSystem->getMasterChannelGroup(&masterGroup);

			m_vecGroups.resize(SOUND_MAX_CHANNEL);

			for (size_t i = 0; i < SOUND_MAX_CHANNEL; i++)
			{
				//m_pSystem->createChannelGroup(result.c_str(), &m_vecGroups[i]);

				masterGroup->addGroup(m_vecGroups[i]);
			}
		}

	}
}