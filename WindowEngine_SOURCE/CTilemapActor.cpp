#include "CTilemapActor.h"
#include "CTilemap.h"
#include "CSprite.h"

#include "CResourceManager.h"
#include "CTimeManager.h"

#include "CCameraComponent.h"
#include "CRenderer.h"
namespace Framework
{
	CTilemapActor::CTilemapActor(UINT32 layer) : CActor(layer)
	{
	}
	void CTilemapActor::BeginPlay()
	{
		SUPER::BeginPlay();
	}
	void CTilemapActor::Release()
	{
		SUPER::Release();
	}
	bool CTilemapActor::Tick()
	{
		SUPER::Tick();
		return true;
	}
	bool CTilemapActor::LastTick()
	{
		SUPER::LastTick();
		return true;
	}
	void CTilemapActor::Render(HDC hdc) const
	{
		if (m_pTilemap == nullptr)
		{
			return;
		}
		if (m_bShowDebug == false)
		{
			return;
		}
		//SUPER::Render(hdc);
		const Maths::Vector2& mapSize = m_pTilemap->GetMapSize();
		const INT32 tileSize = m_pTilemap->GetTileSize();

		const std::vector<std::vector<Tile>>& tiles = m_pTilemap->GetTiles();

		const Resource::CSprite* spriteO = GET_SINGLE(RESOURCE).FindSprite(L"1");
		const Resource::CSprite* sprite1 = GET_SINGLE(RESOURCE).FindSprite(L"2");
		const Maths::Vector2 position = GetPosition();
		const Maths::Vector2 vecTileSize = Maths::Vector2((FLOAT)tileSize, (FLOAT)tileSize);
		const CCameraComponent* mainCam = Renderer::CRenderer::GetMainCamera();

		bool check = true;
		for (INT32 y = 0; y < mapSize.y; y++)
		{
			for (INT32 x = 0; x < mapSize.x; x++)
			{
				if (x < 0 || x >= mapSize.x)
				{
					continue;
				}
				if (y < 0 || y >= mapSize.y)
				{
					continue;
				}
				Maths::Vector2 absolutePos;
				if (mainCam != nullptr)
				{
					const Maths::Vector2 pos = Maths::Vector2(
						(x * tileSize) + position.x, 
						(y * tileSize) + position.y);
					absolutePos = mainCam->CaluatePosition(pos);
					check = mainCam->ScreenInCheck(absolutePos, vecTileSize); //화면 안에 있는지 결과를 반환
				}
				else
				{
					absolutePos.x = position.x + (x * tileSize);
					absolutePos.y = position.y + (y * tileSize);
				}

				if (check == false)
					continue;

				switch (tiles[y][x].value)
				{
				case 0:
					::TransparentBlt(hdc,
						(INT)absolutePos.x,
						(INT)absolutePos.y,
						tileSize, tileSize,
						spriteO->GetHDC(),
						(INT)spriteO->GetSize().x, 
						(INT)spriteO->GetSize().y,
						tileSize, tileSize,
						spriteO->GetTransparent()
					);
					break;
				case 2:

					break;
				default:
					break;
				}
				
			}
		}
	}
}