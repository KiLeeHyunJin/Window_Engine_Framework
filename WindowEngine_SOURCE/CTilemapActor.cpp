#include "CTilemapActor.h"
#include "CTilemap.h"
#include "CSprite.h"

#include "CResourceManager.h"
#include "CTimeManager.h"
#include "CInputManager.h"

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

		const Resource::CSprite* spriteO = GET_SINGLE(RESOURCE).FindSprite(L"1");
		const Resource::CSprite* sprite1 = GET_SINGLE(RESOURCE).FindSprite(L"2");

		//const Maths::Vector2 vecTileSize	= Maths::Vector2(static_cast<FLOAT>(tileSize), static_cast<FLOAT>(tileSize));

		const CCameraComponent* mainCam	= Renderer::CRenderer::GetMainCamera();
		const Maths::Vector2& camPos	= mainCam->GetCameraPosition();
		const Maths::Vector2& position	= GetPosition();

		const Maths::Vector2 resolution = GET_SINGLE(RENDER).GetResolution();


		INT32 startX	= (INT32)((camPos.x - position.x) / m_veciTileSize.x);
		INT32 startY	= (INT32)((camPos.y - position.x) / m_veciTileSize.y);
		INT32 endX		= (INT32)((camPos.x + resolution.x - position.x) / m_veciTileSize.x);
		INT32 endY		= (INT32)((camPos.y + resolution.y - position.y) / m_veciTileSize.y);

		bool check = true;
		for (INT32 y = startY; y <= endY; y++)
		{
			for (INT32 x = startX; x <= endX; x++)
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
					//		(x * tileSize) + position.x, 
					//		(y * tileSize) + position.y);
					//	absolutePos = mainCam->CaluatePosition(pos);
					//	check = mainCam->ScreenInCheck(absolutePos, vecTileSize); //화면 안에 있는지 결과를 반환
					//}
					//else
					//{
					//	absolutePos.x = position.x + (x * tileSize);
					//	absolutePos.y = position.y + (y * tileSize);
					//}
					
					//if (check == false)
					//	continue;
				}


				if (x < startX || x > endX)
					continue;
				if (y < startY || y > endY)
					continue;
				//Maths::Vector2 camStartPos(camPos.x - halfResolution.x, camPos.y - halfResolution.y);


				Maths::Vector2Int setPos(
					(INT32)((position.x + (x * m_veciTileSize.x)) - (camPos.x)),
					(INT32)((position.y + (y * m_veciTileSize.y)) - (camPos.y)));

				//switch (tiles[y][x].value)
				//{
				//case 0:
				//	::TransparentBlt(hdc,
				//		setPos.x,
				//		setPos.y,
				//		m_veciTileSize.x, m_veciTileSize.y,
				//		spriteO->GetHDC(),
				//		(INT)spriteO->GetSize().x, 
				//		(INT)spriteO->GetSize().y,
				//		m_veciTileSize.x, m_veciTileSize.y,
				//		spriteO->GetTransparent()
				//	);
				//	break;
				//case 1:
				//	::TransparentBlt(hdc,
				//		setPos.x,
				//		setPos.y,
				//		m_veciTileSize.x, m_veciTileSize.y,
				//		sprite1->GetHDC(),
				//		(INT)sprite1->GetSize().x,
				//		(INT)sprite1->GetSize().y,
				//		m_veciTileSize.x, m_veciTileSize.y,
				//		spriteO->GetTransparent()
				//	);
				//	break;
				//default:
				//	break;
				//}
				
			}
		}
		return true;
	}

	void CTilemapActor::TileMapPicking()
	{
		if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::LBUTTON))
		{
			CCameraComponent* cam = Renderer::CRenderer::GetMainCamera();
			const Maths::Vector2& camPos = cam->GetCameraPosition();
			const Maths::Vector2& mousePos = GET_SINGLE(INPUT).GetMousePosition();

			const Maths::Vector2 tileNum(
				(mousePos.x + camPos.x) / m_veciTileSize.x,
				(mousePos.y + camPos.y) / m_veciTileSize.y);

			INT32 value = (m_pTilemap->GetTileAt(tileNum).value + 1) % 2;
			m_pTilemap->SetTileAt(tileNum, value);
		}
	}
}