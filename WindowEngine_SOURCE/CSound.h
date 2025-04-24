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

            FMOD::Sound* GetSound()     const   { return m_pSound;          }
            UINT GetChannel()           const   { return m_uiChannel;       }
            void SetChannel(UINT uiChannel)     { m_uiChannel = uiChannel;  }

        private :
            FMOD::Sound* m_pSound   = nullptr;
            UINT m_uiChannel        = 0;

            // CResource��(��) ���� ��ӵ�
            HRESULT Load(const std::wstring& wstrPath) override;

        };
    }
}


