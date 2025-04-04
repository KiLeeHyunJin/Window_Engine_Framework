#pragma once
#include "CommonInclude.h"
#include "CActor.h"
#include "CSprite.h"

namespace Framework
{
	class SpriteActor : public CActor
	{
		SUPER_PARENT(CActor)

		void SetSprite(Resource::CSprite* pSprite) { m_pSprite = pSprite; }

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

