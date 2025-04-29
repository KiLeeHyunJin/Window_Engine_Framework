#include "CTileActor.h"
#include "CPlayerCharacterActor.h"

#include "ContentEnums.h"

#include "..//WindowEngine_SOURCE//CBoxColliderComponent.h"
#include "..//WindowEngine_SOURCE//CRigidbodyComponent.h"
#include "..//WindowEngine_SOURCE//CLineComponent.h"
namespace Framework
{
	CTileActor::CTileActor(UINT layer) : CSpriteActor(layer)
	{
		m_pBoxCollider	= AddComponent<CBoxColliderComponent>();
		m_pRigidbody	= AddComponent<CRigidbodyComponent>();
		m_pLine			= AddComponent<CLineComponent>();

		m_pLine->SetLineHeightPercent(1.f);

		m_pRigidbody->SetFreeze(true);

		m_pBoxCollider->SetTrigger(true);
		m_pBoxCollider->AddCollisionFlag((UINT)eLayer::Character);
	}

	CTileActor::~CTileActor()
	{
	}
	void CTileActor::Initialize()
	{
		SUPER::Initialize();
	}

	void CTileActor::BeginPlay()
	{
		SUPER::BeginPlay();

		m_pBoxCollider->Initialize();
		m_pLine->Initialize();
	}
	void CTileActor::Release()
	{
		SUPER::Release();
	}
	bool CTileActor::Tick()
	{
		bool result = SUPER::Tick();
		return result;
	}
	bool CTileActor::LastTick()
	{
		bool result = SUPER::Tick();

		return result;
	}
	void CTileActor::FixedTick()
	{
		SUPER::FixedTick();

	}
	bool CTileActor::Render(HDC hdc) const
	{
		if (SUPER::Render(hdc) == false)
		{		return false;	}

		return false;
	}

	void CTileActor::OnCollisionEnter(CColliderComponent* other)
	{
	}

	void CTileActor::OnCollisionStay(CColliderComponent* other)
	{
		CActor* pOtherOWner = other->GetOwner();
		CPlayerCharacterActor* pPlayerCharacter = dynamic_cast<CPlayerCharacterActor*>(pOtherOWner);

		if (pPlayerCharacter == nullptr)
			return;

		const CBoxColliderComponent* pBoxColl	= dynamic_cast<CBoxColliderComponent*>(other);
		CheckCollisionLine(pBoxColl);
	}

	void CTileActor::OnCollisionExit(CColliderComponent* other)
	{
	}

	bool CTileActor::CheckCollisionLine(const CBoxColliderComponent* target)
	{
		if (m_pLine->GetTrigger())
		{		return false;	}

		CActor* targetOwner = target->GetOwner();
		const Maths::Vector2 pos = targetOwner->GetPosition() + target->GetOffset();
		//const Maths::Vector2& size = target->GetSize();

		float lineYPos;
		//if (m_pLine->CheckCollisionX(pos.x + size.x * 0.5f) == false &&
		//	m_pLine->CheckCollisionX(pos.x - size.x * 0.5f) == false)
		//{		
		//	return false;	
		//}

		if (m_pLine->GetPositionY(pos.x, &lineYPos) == false)
		{		return false;	}

		if (lineYPos > pos.y) //선보다 위
		{		return false;	}

		//선 높이랑 플레이어 높이가 플레이어의 콜라이더 박스 높이의 20% 보다 크다면 충돌 인정 X 
		if (Maths::Abs(lineYPos - pos.y) > (target->GetSize().y * 0.12f))
		{		return false;	}

		targetOwner->SetPosition(Maths::Vector2(pos.x, lineYPos));
		CRigidbodyComponent* pRigidbody = targetOwner->GetComponent<CRigidbodyComponent>();
		if (pRigidbody != nullptr)
		{
			pRigidbody->SetGround(true);
		}
		return true;
	}


}