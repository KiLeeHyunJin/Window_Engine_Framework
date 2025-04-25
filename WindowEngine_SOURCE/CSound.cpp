#include "CSound.h"
#include "CSoundManager.h"
namespace Framework
{
    namespace Resource
    {
        CSound::CSound() : CResource(Enums::eResourceType::AudioClip)
        {
        }

        CSound::~CSound()
        {
        }

        HRESULT CSound::Load(const std::wstring& wstrPath)
        {
            char str[255];
			wcstombs_s(nullptr, str, wstrPath.c_str(), 255);
            GET_SINGLE(SOUND).GetSystem()->createSound(str, FMOD_DEFAULT, 0, &m_pSound);
            return S_OK;
        }


    }
}