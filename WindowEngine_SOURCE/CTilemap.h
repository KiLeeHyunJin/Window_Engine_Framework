#pragma once
#include "CScene.h"

namespace Framework
{
	struct Tile
	{
		INT32 value = 0;

	};

	class CTilemap :
		public CScene
	{
	public:
		// CScene을(를) 통해 상속됨
		void OnEnter() override;
		void OnExit() override;
		void Initialize() override;
		void Release() override;
		void Tick() override;
		void LastTick() override;
		void Render(HDC hdc) override;

		const Maths::Vector2&					GetMapSize()						const { return m_vecMapSize; }
		const INT32								GetTileSize()						const { return m_iTileSize; }
		const Tile&								GetTileAt(const Maths::Vector2 pos) const { return m_vecTiles[(INT)pos.y][(INT)pos.x]; }
		const std::vector<std::vector<Tile>>&	GetTiles()							const { return m_vecTiles; }
		
		void		SetTileSize(INT32 size)				{ m_iTileSize = size; }
		void		SetMapSize(Maths::Vector2 size);

	private:
		Maths::Vector2 m_vecMapSize						= Maths::Vector2::Zero;
		INT32 m_iTileSize								= 0;
		std::vector<std::vector<Tile>> m_vecTiles		= {};

	};
}

