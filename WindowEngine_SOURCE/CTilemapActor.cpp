#include "CTilemapActor.h"
#include "CTilemap.h"
#include "CSprite.h"

#include "CResourceManager.h"
#include "CTimeManager.h"
#include "CInputManager.h"
#include "CRenderManager.h"

#include "CCameraComponent.h"

#include "CRenderer.h"
namespace Framework
{
	CTilemapActor::CTilemapActor(UINT32 layer) : CActor(layer)
	{
	}
	void CTilemapActor::Initialize()
	{
		SUPER::Initialize();
	}

	void CTilemapActor::BeginPlay()
	{
		SUPER::BeginPlay();
		//TODO
	}
	void CTilemapActor::Release()
	{
		SUPER::Release();
		//TODO
	}
	bool CTilemapActor::Tick()
	{
		SUPER::Tick();
		//TODO

		TileMapPicking();

		return true;
	}
	bool CTilemapActor::LastTick()
	{
		SUPER::LastTick();
	
		const INT32 tileSize = m_pTilemap->GetTileSize();
		this->m_veciTileSize = Maths::Vector2Int(tileSize);
		//TODO
		return true;
	}

	void CTilemapActor::FixedTick()
	{

	}

	bool CTilemapActor::Render(HDC hdc) const
	{
		if (m_pTilemap == nullptr)
		{
			return false;
		}
		if (m_bShowDebug == false)
		{
			return false;
		}
		//SUPER::Render(hdc);


		const Maths::Vector2& mapSize = m_pTilemap->GetMapSize();
		const std::vector<std::vector<Tile>>& tiles = m_pTilemap->GetTiles();


		//const Maths::Vector2 vecTileSize	= Maths::Vector2(static_cast<FLOAT>(tileSize), static_cast<FLOAT>(tileSize));

		const CCameraComponent* mainCam	= Renderer::CRenderer::GetMainCamera();
		const Maths::Vector2& camPos	= mainCam->GetCameraPosition();
		const Maths::Vector2& position	= GetPosition();

		const Maths::Vector2 resolution = GET_SINGLE(RENDER).GetResolution();


		INT32 startX	= (INT32)((camPos.x - position.x) / m_veciTileSize.x);
		INT32 startY	= (INT32)((camPos.y - position.x) / m_veciTileSize.y);
		INT32 endX		= (INT32)((camPos.x + resolution.x - position.x + (m_veciTileSize.x * 0.5f)) / m_veciTileSize.x);
		INT32 endY		= (INT32)((camPos.y + resolution.y - position.y) / m_veciTileSize.y);

		const Maths::Vector2 pos = position - camPos;

		bool check = true;	
		for (INT32 y = startY; y < endY; y++)
		{
			for (INT32 x = startX; x < endX; x++)
			{
				if (x < 0 || x >= mapSize.x)
				{
					continue;
				}
				if (y < 0 || y >= mapSize.y)
				{
					continue;
				}
				{
					//Maths::Vector2 absolutePos;
					//if (mainCam != nullptr)
					//{
					//	const Maths::Vector2 pos = Maths::Vector2(
					//		(x * m_veciTileSize.x) + position.x, 
					//		(y * m_veciTileSize.y) + position.y);
					//	absolutePos = mainCam->CaluatePosition(pos);
					//	check = mainCam->ScreenInCheck(absolutePos, m_veciTileSize); //화면 안에 있는지 결과를 반환
					//}
					//else
					//{
					//	absolutePos.x = position.x + (x * m_veciTileSize.x);
					//	absolutePos.y = position.y + (y * m_veciTileSize.y);
					//}
					
					//if (check == false)
					//	continue;
				}


			/*	if (x < startX || x > endX)
					continue;
				if (y < startY || y > endY)
					continue;*/
				//Maths::Vector2 camStartPos(camPos.x - halfResolution.x, camPos.y - halfResolution.y);


				Maths::Vector2Int startPos = pos + 
					Maths::Vector2(
						(FLOAT)(x * m_veciTileSize.x) + m_veciTileSize.x * 0.5f,
						(FLOAT)(y * m_veciTileSize.y) + m_veciTileSize.y);

				switch (tiles[y][x].value)
				{
				case 0:
				{
					const Resource::CSprite* sprite = GET_SINGLE(RESOURCE).FindSprite(L"1");
					if (sprite == nullptr)
						break;
					GET_SINGLE(RENDER).Image(sprite, startPos);
				}
					break;	  

				case 1:
				{
					const Resource::CSprite* sprite = GET_SINGLE(RESOURCE).FindSprite(L"2");
					if (sprite == nullptr)
						break;
					GET_SINGLE(RENDER).Image(sprite, startPos);
				}
					break;

				default:
					break;
				}


				
			}
		}
		return true;
	}

	void CTilemapActor::TileMapPicking()
	{
		if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::LBUTTON))
		{
			const CCameraComponent* cam = Renderer::CRenderer::GetMainCamera();
			const Maths::Vector2& camPos = cam->GetCameraPosition();
			const Maths::Vector2& mousePos = GET_SINGLE(INPUT).GetMousePosition();

			const Maths::Vector2 tileNum(
				(mousePos.x + camPos.x ) / m_veciTileSize.x,
				(mousePos.y + camPos.y ) / m_veciTileSize.y);
			const INT32 value = (m_pTilemap->GetTileAt(tileNum).value + 1) % 2;
			m_pTilemap->SetTileAt(tileNum, value);
		}
	}
}