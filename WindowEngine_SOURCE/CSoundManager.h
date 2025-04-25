#pragma once
#include "CommonInclude.h"



namespace Framework
{
	namespace Resource
	{
		class CSound;
	}

	class CSoundChannel;

	namespace Manager
	{
		class CSoundManager
		{

			DECLARE_SINGLE(CSoundManager)
			RELEASE_SINGLE(CSoundManager)
		public:
			enum class eSoundGroup
			{
				Background,
				Effect,
				UI,
				Voice,
				Size
			};

		public:
			void Initialize();
			void Tick();
			void SetGroup(std::vector<eSoundGroup>& channelGroups);

			FMOD::System*		GetSystem()						const { return m_pSystem;									}
			FMOD::ChannelGroup* GetGroup(eSoundGroup eGroup)	const { return m_vecGroups[(UINT)eGroup];					}
			CSoundChannel*		GetChannel(UINT channelNum)		const { return m_vecChannels[channelNum];					}

			void SetMasterVolume(float fVolume)						{ m_pMasterGroup->setVolume(Maths::Clamp<FLOAT>(fVolume, 0, 1));}
			void SetMasterPitch(float fPitch)						{ m_pMasterGroup->setPitch(fPitch);								}
			void SetMasterMute(bool state)							{ m_pMasterGroup->setMute(state);								}
			void SetMasterPaused(bool state)						{ m_pMasterGroup->setPaused(state);								}
			void SetLowPass(eSoundGroup eGroup, bool state)			{ m_vecDspLowpass[(UINT)eGroup]->setBypass(state);				}
			void SetHighPass(eSoundGroup eGroup, bool state)		{ m_vecDspHighpass[(UINT)eGroup]->setBypass(state);				}

			void GetMasterVolume(float* fVolume)			const	{ m_pMasterGroup->getVolume(fVolume);							}
			void GetMasterPitch(float* fPitch)			const		{ m_pMasterGroup->getPitch(fPitch);								}
			void GetMasterMute(bool* bMute)				const		{ m_pMasterGroup->getMute(bMute);								}
			void GetMasterPaused(bool* bPaused)			const		{ m_pMasterGroup->getPaused(bPaused);							}
			bool GetLowPass(eSoundGroup eGroup)		const;
			bool GetHighPass(eSoundGroup eGroup)	const;

			void ResetPass(eSoundGroup eGroup);

			CSoundChannel* SetSoundClip(const Resource::CSound* pSound, bool bLoop = false);


		private:
			void CreateGroup();
			void Release();

			FMOD::System* m_pSystem = nullptr;
			FMOD::ChannelGroup* m_pMasterGroup = nullptr;

			std::vector<CSoundChannel*> m_vecChannels = {};
			std::vector<FMOD::ChannelGroup*> m_vecGroups = {};

			std::vector<FMOD::DSP*> m_vecDspLowpass		= {};
			std::vector<FMOD::DSP*> m_vecDspHighpass	= {};
			std::vector<FMOD::DSP*> m_vecDspCompressor	= {};;
		};

	}
	using SOUND = Manager::CSoundManager;
}