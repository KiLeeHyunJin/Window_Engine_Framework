#include "CFlipbook.h"

namespace Framework
{
    namespace Resource
    {
        CFlipbook::CFlipbook(bool loop) : CResource(Enums::eResourceType::Animation), m_bLoop(loop)
        {
        }
        CFlipbook::~CFlipbook()
        {
        }
        HRESULT CFlipbook::Load(const std::wstring& wstrPath)
        {
            return S_OK;
        }
    }
}