#include "CPlayScene.h"
#include "..\\WindowEngine_SOURCE\\Object.h"

#include "CInputManager.h"
#include "CSceneManager.h"
#include "CResourceManager.h"
#include "CCollisionManager.h"

#include "CCameraComponent.h"

#include "CActor.h"
#include "CRenderer.h"
#include "CTexture.h"

#include "CPlayerInput.h"
#include "CDummy.h"

#include "ContentsEnums.h"
#include "CSpriteActor.h"
#include "CFlipbook.h"
#include "CFlipbookActor.h"

Framework::CPlayScene::CPlayScene()
{
}

Framework::CPlayScene::~CPlayScene()
{
}

void Framework::CPlayScene::Initialize()
{
	const Resource::CTexture* pTexture = GET_SINGLE(RESOURCE).FindTexture(L"Room");

	
}

void Framework::CPlayScene::Tick()
{
	if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::B))
	{
		GET_SINGLE(EVENT).LoadScene((UINT)eMap::Title, 1);
	}
	
	if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::V))
	{
		if (m_list.size() != 0)
		{
			for (auto pObj : m_list)
			{
				Object::Destroy(pObj);
			}
		}
		m_list.clear();
	}
}

void Framework::CPlayScene::LastTick()
{
}

void Framework::CPlayScene::Render(HDC hdc)
{
}

void Framework::CPlayScene::Release()
{
}

void Framework::CPlayScene::OnEnter()
{
	GET_SINGLE(COLLISION).SetCollisionLayerState((UINT)Enums::eLayerType::BackGround, (UINT)Enums::eLayerType::BackGround, true);

	const Resource::CTexture* pTexture = GET_SINGLE(RESOURCE).FindTexture(L"Room");
	const Resource::CTexture* pTexture1 = GET_SINGLE(RESOURCE).FindTexture(L"Room1");
	const Resource::CTexture* pTexture2 = GET_SINGLE(RESOURCE).FindTexture(L"Room2");

	GET_SINGLE(RESOURCE).CreateSprite(pTexture, L"Room", Maths::Vector2Int(0, 0), Maths::Vector2Int(pTexture->GetWidth(), pTexture->GetHeight()));
	GET_SINGLE(RESOURCE).CreateSprite(pTexture1, L"Room1", Maths::Vector2Int(0, 0), Maths::Vector2Int(pTexture->GetWidth(), pTexture->GetHeight()));
	GET_SINGLE(RESOURCE).CreateSprite(pTexture2, L"Room2", Maths::Vector2Int(0, 0), Maths::Vector2Int(pTexture->GetWidth(), pTexture->GetHeight()));

	GET_SINGLE(RESOURCE).CreateFlipbook(L"Room", false);
	const Resource::CFlipbook* flipBook = GET_SINGLE(RESOURCE).FindFlipbook(L"Room");

	const Resource::CSprite* sprite1 = GET_SINGLE(RESOURCE).FindSprite(L"Room");
	const Resource::CSprite* sprite2 = GET_SINGLE(RESOURCE).FindSprite(L"Room1");
	const Resource::CSprite* sprite3 = GET_SINGLE(RESOURCE).FindSprite(L"Room2");

	GET_SINGLE(RESOURCE).InsertSprite(flipBook, sprite1);
	GET_SINGLE(RESOURCE).InsertSprite(flipBook, sprite2);
	GET_SINGLE(RESOURCE).InsertSprite(flipBook, sprite3);


	CFlipbookActor* pSpriteActor = Object::Instantiate<CFlipbookActor>(3, L"SpriteActor");
	pSpriteActor->SetPosition(Maths::Vector2(50, 50));

	pSpriteActor->SetFlipbook(flipBook);

	//for (size_t i = 0; i < 200; i++)
	//{
	//	CActor* pObj =
	//		Object::Instantiate<CDummy>((UINT)Enums::eLayerType::BackGround, L"Dummy")->GetOwner();
	//	CBoxColliderComponent* pBoxColl =
	//		pObj->AddComponent<CBoxColliderComponent>();
	//	CRigidbodyComponent* pRigid =
	//		pObj->AddComponent<CRigidbodyComponent>();

	//	pRigid->SetGround(true);
	//	pObj->AddComponent<CPlayerInput>();

	//	pBoxColl->SetSize(Maths::Vector2(50, 50));
	//	pObj->GetTransformComponent()->SetPos(Maths::Vector2((float)(100 + i * 10), (float)(100 + i * 10)));
	//	pObj->GetTransformComponent()->SetScale(Maths::Vector2(50, 50));

	//	m_list.push_back(pObj);
	//}
	
}

void Framework::CPlayScene::OnExit()
{
	//m_list.clear();
}

//void Framework::CPlayScene::LastRender(HDC hdc)
//{
//}
