#pragma once
#include "CommonInclude.h"
#include "CActor.h"
#include "CSprite.h"

namespace Framework
{
	class CSpriteActor : public CActor
	{
		DECLARE_PARENT(CActor)
	public:
		CSpriteActor(UINT layer);
		virtual ~CSpriteActor();

		void SetSprite( const Resource::CSprite* pSprite) { m_pSprite = const_cast<Resource::CSprite*>(pSprite); }

	protected:
		// CActor을(를) 통해 상속됨
		void BeginPlay() override;
		void Release() override;
		bool Tick() override;
		bool LastTick() override;
		void Render(HDC hdc) const override;

	private:
		Resource::CSprite* m_pSprite;
	};


}

