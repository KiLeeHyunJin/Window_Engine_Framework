#pragma once
#include "CResource.h"
#include "CommonInclude.h"

namespace Framework
{
    namespace Resource
    {
        class CResourceManager;
        class CSprite;
           
        class CFlipbook :
            public CResource
        {
        public:
            bool GetLoop() const                                                { return m_bLoop; }
            INT GetSize() const                                                { return (UINT)m_vecSprites.size() - 1; }
 
            const std::pair<const CSprite*, float>& GetPair(UINT index) const   { return m_vecSprites[index]; }
            float GetDuration(UINT index) const                                 { return m_vecSprites[index].second; }
            const CSprite* GetSprite(UINT index) const                          { return m_vecSprites[index].first; }

            friend Manager::CResourceManager;
        private:
            CFlipbook(bool loop);
            virtual ~CFlipbook();

            void AddSprite(const CSprite* sprite, float duration) { m_vecSprites.push_back(std::make_pair(sprite, duration)); }

            std::vector<std::pair<const CSprite*,float>> m_vecSprites;
            bool m_bLoop;

            // CResource을(를) 통해 상속됨
            HRESULT Load(const std::wstring& wstrPath) override;
        };
    }
}


