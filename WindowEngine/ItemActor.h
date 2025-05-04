#pragma once
#include "..//WindowEngine_SOURCE//CSpriteActor.h"


namespace Framework
{

    class ItemActor :
        public CSpriteActor
    {
    public:
		ItemActor(INT layer);
		virtual ~ItemActor();

		void Initialize()			override;
		void BeginPlay()			override;
		void Release()				override;
		bool Tick()					override;
		bool LastTick()				override;
		void FixedTick()			override;
		bool Render(HDC hdc) const	override;
    private:

    };
}


