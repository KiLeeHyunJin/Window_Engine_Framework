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
	const Resource::CTexture* pTexture = Resource::CResourceManager::FindTexture(L"Room");

	//CActor* pObj = Object::Instantiate<CPlayerInput>((UINT)Enums::eLayerType::BackGround, L"Player")->GetOwner();
	//CBoxColliderComponent* pBoxColl = pObj->AddComponent<CBoxColliderComponent>();
	//CRigidbodyComponent* pRigid = pObj->AddComponent<CRigidbodyComponent>();
	//CAnimatorComponent* pAnim = pObj->AddComponent<CAnimatorComponent>();
	//pAnim->CreateAnimationByFolder(L"Temp", L"..\\Resources\\", 1);

	////pAnim->CreateAnimation(L"Temp", pTexture, Maths::Vector2(0, 50), 3, 2);

	//pAnim->PlayAnimation(L"Temp");
	//pRigid->SetGround(true);

	////CPlayerInput* pInput = pObj->AddComponent<CPlayerInput>();
	//pObj->GetTransformComponent()->SetPos(Maths::Vector2(100, 100));

	//CAnimatorComponent* pAnim = pObj->AddComponent<CAnimatorComponent>();
	//pAnim->CreateAnimation(L"Room", pTexture, Vector2::Zero, Vector2(50, 50), Vector2::Zero, 5, 0.2f);
	//pAnim->PlayAnimation(L"Room", true);


	/*pObj = Object::Instantiate<CDummy>((UINT)Enums::eLayerType::BackGround, L"Dummy")->GetOwner();
	pBoxColl = pObj->AddComponent<CBoxColliderComponent>();
	pRigid = pObj->AddComponent<CRigidbodyComponent>();
	
	pRigid->SetGround(true);
	pBoxColl->SetSize(Maths::Vector2(50, 50));

	pObj->GetTransformComponent()->SetPos(Maths::Vector2(100, 100));
	pObj->GetTransformComponent()->SetScale(Maths::Vector2(50, 50));


	CCollisionManager::SetCollisionLayerState((UINT)Enums::eLayerType::BackGround, (UINT)Enums::eLayerType::BackGround, true);*/


	//pObj->AddComponent<CPlayerInput>();


	//CActor* pCameraObj = Object::Instantiate((UINT)Enums::eLayerType::None, L"Cam");
	
	//CCameraComponent* pCamera = pCameraObj->AddComponent<CCameraComponent>();

	//Object::DontDestoryOnLoad(pCameraObj);
	
	//Renderer::CRenderer::SetMainCamera(pCamera);

	
}

void Framework::CPlayScene::TickComponent()
{
	if (INPUT::GetKeyDown(eKeyCode::B))
	{
		EVENT::LoadScene((UINT)eMap::Title, 1);
	}
	
	if (INPUT::GetKeyDown(eKeyCode::V))
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

void Framework::CPlayScene::LastTickComponent()
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
	COLLISION::SetCollisionLayerState((UINT)Enums::eLayerType::BackGround, (UINT)Enums::eLayerType::BackGround, true);

	const Resource::CTexture* pTexture = Resource::CResourceManager::FindTexture(L"Room");
	const Resource::CTexture* pTexture1 = Resource::CResourceManager::FindTexture(L"Room1");
	const Resource::CTexture* pTexture2 = Resource::CResourceManager::FindTexture(L"Room2");

	Resource::CResourceManager::CreateSprite(pTexture, L"Room", Maths::Vector2Int(0, 0), Maths::Vector2Int(pTexture->GetWidth(), pTexture->GetHeight()));
	Resource::CResourceManager::CreateSprite(pTexture1, L"Room1", Maths::Vector2Int(0, 0), Maths::Vector2Int(pTexture->GetWidth(), pTexture->GetHeight()));
	Resource::CResourceManager::CreateSprite(pTexture2, L"Room2", Maths::Vector2Int(0, 0), Maths::Vector2Int(pTexture->GetWidth(), pTexture->GetHeight()));

	Resource::CResourceManager::CreateFlipbook(L"Room", false);
	const Resource::CFlipbook* flipBook = Resource::CResourceManager::FindFlipbook(L"Room");

	const Resource::CSprite* sprite1 = Resource::CResourceManager::FindSprite(L"Room");
	const Resource::CSprite* sprite2 = Resource::CResourceManager::FindSprite(L"Room1");
	const Resource::CSprite* sprite3 = Resource::CResourceManager::FindSprite(L"Room2");

	Resource::CResourceManager::InsertSprite(flipBook, sprite1);
	Resource::CResourceManager::InsertSprite(flipBook, sprite2);
	Resource::CResourceManager::InsertSprite(flipBook, sprite3);

	CFlipbookActor* pSpriteActor = new CFlipbookActor(3);
	pSpriteActor->SetPosition(Maths::Vector2(50, 50));
	CEventManager::AddActor(CSceneManager::GetCurrentScene(), pSpriteActor, false);

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

void Framework::CPlayScene::LastRender(HDC hdc)
{
}
