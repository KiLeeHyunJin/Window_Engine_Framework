#pragma once
#include "CActor.h"


namespace Framework
{
	class CTilemap;


	class CTilemapActor : public CActor
	{
		DECLARE_PARENT(CActor)
	public:
		CTilemapActor(UINT32 layer);

		// CActor��(��) ���� ��ӵ�
		void		BeginPlay() override;
		void		Release() override;
		bool		Tick() override;
		bool		LastTick() override;
		void		Render(HDC hdc) const override;

		CTilemap*	GetTilemap()		const		{ return m_pTilemap;		}

		void		SetTilemap(CTilemap* pTilemap)	{ m_pTilemap = pTilemap;	}
		void		SetShowDebug(bool state)		{ m_bShowDebug = state;		}
	private:

			CTilemap* m_pTilemap	= nullptr;
			bool m_bShowDebug		= false;
	public:

	};
}

