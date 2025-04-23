#pragma once
#include "CommonInclude.h"
#include "Define.h"


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
			CSoundChannel*		GetChannel(UINT channelNum)		const { return m_vecChannels[channelNum];					}
			FMOD::ChannelGroup* GetGroup(eSoundGroup eGroup)	const { return m_vecGroups[(UINT)eGroup];					}

			void SetVolume(float fVolume)						{ masterGroup->setVolume(Maths::Clamp<FLOAT>(fVolume, 0, 1));}
			void SetPitch(float fPitch)							{ masterGroup->setPitch(fPitch);							}
			void SetMute(bool state)							{ masterGroup->setMute(state);								}
			void SetPaused(bool state)							{ masterGroup->setPaused(state);							}
			void SetLowPass(eSoundGroup eGroup, bool state)		{ m_vecDspLowpass[(UINT)eGroup]->setBypass(state);			}
			void SetHighPass(eSoundGroup eGroup, bool state)	{ m_vecDspHighpass[(UINT)eGroup]->setBypass(state);			}

			void GetVolume(float* fVolume)			const		{ masterGroup->getVolume(fVolume);							}
			void GetPitch(float* fPitch)			const		{ masterGroup->getPitch(fPitch);							}
			void GetMute(bool* bMute)				const		{ masterGroup->getMute(bMute);								}
			void GetPaused(bool* bPaused)			const		{ masterGroup->getPaused(bPaused);							}
			bool GetLowPass(eSoundGroup eGroup)		const;
			bool GetHighPass(eSoundGroup eGroup)	const;

			void ResetPass(eSoundGroup eGroup);

			CSoundChannel* SetSoundClip(const Resource::CSound* pSound, bool bLoop = false);


		private:
			void CreateGroup();
			void Release();

			//void LoadSoundFile();


			// 사운드 ,채널 객체 및 장치를 관리하는 객체 
			FMOD::System* m_pSystem = nullptr;
			FMOD::ChannelGroup* masterGroup = nullptr;
			std::vector<CSoundChannel*> m_vecChannels = {};
			std::vector<FMOD::ChannelGroup*> m_vecGroups = {};

			std::vector<FMOD::DSP*> m_vecDspLowpass		= {};
			std::vector<FMOD::DSP*> m_vecDspHighpass	= {};
			std::vector<FMOD::DSP*> m_vecDspCompressor	= {};;
			//std::vector<FMOD::ChannelGroup*> m_vecGroups;
		};

	}
	using SOUND = Manager::CSoundManager;
}