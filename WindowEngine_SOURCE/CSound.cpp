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
            std::wstring mediaPrefix = L"..//Resources//Sound//";
            std::wstring path = mediaPrefix.append(wstrPath);
            
            char str[255];
			wcstombs_s(nullptr, str, path.c_str(), 255);
            GET_SINGLE(SOUND).GetSystem()->createSound(str, FMOD_LOOP_NORMAL, 0, &m_pSound);
            return E_NOTIMPL;
        }


    }
}