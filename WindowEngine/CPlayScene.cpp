#include "CPlayScene.h"
#include "..\\WindowEngine_SOURCE\\Object.h"

#include "CInputManager.h"
#include "CSceneManager.h"
#include "CResourceManager.h"
#include "CCollisionManager.h"

#include "CCameraComponent.h"
#include "CBoxColliderComponent.h"
#include "CRigidbodyComponent.h"

#include "CRenderer.h"
#include "CFlipbook.h"
#include "CTexture.h"
#include "ContentEnums.h"


#include "CActor.h"
#include "CSpriteActor.h"
#include "CFlipbookActor.h"
#include "CGameControllActor.h"


Framework::CPlayScene::CPlayScene()
{
}

Framework::CPlayScene::~CPlayScene()
{
}

void Framework::CPlayScene::Initialize()
{
	const Resource::CTexture* pTexture = GET_SINGLE(RESOURCE).FindTexture(L"Room");
	//GET_SINGLE(OBJECT).CreateObject<CGameControllActor>((UINT)eLayer::None, true);

	
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
	GET_SINGLE(COLLISION).SetCollisionLayerState((UINT)eLayer::Character, (UINT)eLayer::Character, true);

	//CActor* pActor = Object::Instantiate<CPlayerControllActor>((UINT)eLayer::Character, L"Test");
	//pActor->AddComponent<CRigidbodyComponent>();
	//CBoxColliderComponent* pBoxColl = pActor->AddComponent<CBoxColliderComponent>();
	//pBoxColl->AddCollisionFlag((UINT)eLayer::Character);
	//pBoxColl->SetSize(Maths::Vector2(50, 50));
	//pActor->SetPosition(Maths::Vector2(50,50));

	{
		CActor* pActor = Object::Instantiate<CSpriteActor>((UINT)eLayer::Character, L"Dest");
		CBoxColliderComponent* pBoxColl = pActor->AddComponent<CBoxColliderComponent>();
		pBoxColl->AddCollisionFlag((UINT)eLayer::Character);
		pBoxColl->SetSize(Maths::Vector2(50, 50));
		pActor->SetLocalPosition(Maths::Vector2(200, 70));
	}
	{
		CActor* pActor = Object::Instantiate<CSpriteActor>((UINT)eLayer::Character, L"Dest");
		CBoxColliderComponent* pBoxColl = pActor->AddComponent<CBoxColliderComponent>();
		pBoxColl->AddCollisionFlag((UINT)eLayer::Character);
		pBoxColl->SetSize(Maths::Vector2(50, 50));
		pActor->SetLocalPosition(Maths::Vector2(260, 70));
	}
	{
		CActor* pActor = Object::Instantiate<CSpriteActor>((UINT)eLayer::Character, L"Dest");
		CBoxColliderComponent* pBoxColl = pActor->AddComponent<CBoxColliderComponent>();
		pBoxColl->AddCollisionFlag((UINT)eLayer::Character);
		pBoxColl->SetSize(Maths::Vector2(50, 50));
		pActor->SetLocalPosition(Maths::Vector2(320, 70));
	}

	//for (UINT i = 0; i < 200; i++)
	//{
	//	pActor = Object::Instantiate<CSpriteActor>((UINT)eLayer::Monster, L"Dest");
	//	pBoxColl = pActor->AddComponent<CBoxColliderComponent>();
	//	pBoxColl->AddCollisionFlag((UINT)eLayer::Character);
	//	pBoxColl->SetSize(Maths::Vector2(50, 50));
	//	pActor->SetPosition(Maths::Vector2(400, 100));
	//}



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
