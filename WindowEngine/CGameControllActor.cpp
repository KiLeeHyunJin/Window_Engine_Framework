#include "CGameControllActor.h"
#include "ContentEnums.h"

namespace Framework
{

    namespace Content
    {
        CGameControllActor::CGameControllActor() : CActor((UINT)eLayer::None)
        {
            static bool create= false;
            if (create)
            {
                assert(false);
            }
            create = !creat;
        }

        CGameControllActor::~CGameControllActor()
        {   }




    }
}
