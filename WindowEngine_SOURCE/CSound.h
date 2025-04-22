#pragma once
#include "CResource.h"
namespace Framework
{
    namespace Resource
    {
        class CSound :
            public CResource
        {
        public :
            CSound();
            virtual ~CSound();

            FMOD::Sound* GetSound() { return m_pSound; }


        private :
            FMOD::Sound* m_pSound;


            // CResource을(를) 통해 상속됨
            HRESULT Load(const std::wstring& wstrPath) override;

        };
    }
}


