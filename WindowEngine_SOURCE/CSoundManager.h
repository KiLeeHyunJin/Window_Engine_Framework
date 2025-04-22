#pragma once
#include "CommonInclude.h"
#include "Define.h"
#include "CSoundChannel.h"


namespace Framework
{
	namespace Resource
	{
		class CSound;
	}
	namespace Manager
	{
		class CSoundManager
		{
			DECLARE_SINGLE(CSoundManager)
			RELEASE_SINGLE(CSoundManager)
		public:
			enum class eSoundChannel
			{
				Master, Channel
			};
		public:
			void Initialize();
			void Release();
			void Tick();

			void PlaySound(Resource::CSound* pSound, UINT iChannel, float fVolume);
			FMOD::System* GetSystem() { return m_pSystem; }

			void PlayBGM(Resource::CSound* pSound, float fVolume);

			void StopAll();

			CSoundChannel* GetChannel(UINT channelNum) { return m_vecChannel[channelNum]; }

			void SetVolume(float fVolume) { masterGroup->setVolume(fVolume); }
			void SetPitch(float fPitch) { masterGroup->setPitch(fPitch); }
			void SetMute(bool state) { masterGroup->setMute(state); }
			void GetMute(bool* bMute) { masterGroup->getMute(bMute); }

		private:
			void CreateGroup();

			//void LoadSoundFile();


			// 사운드 ,채널 객체 및 장치를 관리하는 객체 
			FMOD::System* m_pSystem = nullptr;
			FMOD::ChannelGroup* masterGroup = nullptr;
			std::vector<CSoundChannel*> m_vecChannel;
			std::vector<FMOD::ChannelGroup*> m_vecGroups;
		};

	}
	using SOUND = Manager::CSoundManager;
}