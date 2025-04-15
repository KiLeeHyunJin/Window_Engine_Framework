#include "CTilemap.h"


namespace Framework
{
	void CTilemap::OnEnter()
	{
	}
	void CTilemap::OnExit()
	{
	}
	void CTilemap::Initialize()
	{
	}
	void CTilemap::Release()
	{
	}
	void CTilemap::Tick()
	{
	}
	void CTilemap::LastTick()
	{
	}
	void CTilemap::Render(HDC hdc)
	{
	}
	void CTilemap::SetMapSize(Maths::Vector2 size)
	{
		m_vecMapSize = size;
		m_vecTiles = std::vector<std::vector<Tile>>((INT)size.y, std::vector<Tile>((INT)size.x));
		for (INT32 y = 0; y < size.y; y++)
		{
			for (INT32 x = 0; x < size.x; x++)
			{
				m_vecTiles[y][x] = Tile{};
			}
		}
	}
}