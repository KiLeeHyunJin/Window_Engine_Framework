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

		m_pLine->SetLineHeightPercent(.7f);

		m_pRigidbody->SetFreeze(true);

		m_pBoxCollider->SetTrigger(true);
		m_pBoxCollider->AddCollisionFlag((UINT)eLayer::Character);
	}

	CTileActor::~CTileActor()
	{
	}

	bool CTileActor::TileAdjustPosition(CBoxColliderComponent* targetCollider)
	{
		if (targetCollider == nullptr)
		{		return false;	}

		CActor* pOtherOWner = targetCollider->GetOwner();
		CPlayerCharacterActor* pPlayerCharacter = dynamic_cast<CPlayerCharacterActor*>(pOtherOWner);

		if (pPlayerCharacter == nullptr)
			return false;

		return CheckCollisionLine(targetCollider);
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
		//CBoxColliderComponent* pBoxColl = dynamic_cast<CBoxColliderComponent*>(other);
		//TileAdjustPosition(pBoxColl);
	}

	void CTileActor::OnCollisionStay(CColliderComponent* other)
	{
		/*CBoxColliderComponent* pBoxColl = dynamic_cast<CBoxColliderComponent*>(other);
		TileAdjustPosition(pBoxColl);*/
	}

	bool CTileActor::CheckCollisionLine(const CBoxColliderComponent* target)
	{
		if (m_pLine->GetTrigger())
		{		return false;	}

		CActor* targetOwner = target->GetOwner();
		const Maths::Vector2 pos = targetOwner->GetPosition() + target->GetOffset();

		float lineYPos;

		if (m_pLine->GetPositionY(pos.x, &lineYPos) == false)
		{		return false;	}

		if (lineYPos > pos.y) //선보다 위
		{		return false;	}

		//선 높이랑 플레이어 높이가 플레이어의 콜라이더 박스 높이의 20% 보다 크다면 충돌 인정 X 
		const float length = Maths::Abs(lineYPos - pos.y);
		const float targetSizeIgnoreLenth = target->GetSize().y * 0.12f;
		if (length > targetSizeIgnoreLenth)
		{		return false;	}

		lineYPos += 0.05f;
		targetOwner->SetPosition(Maths::Vector2(pos.x, lineYPos));
		return true;
	}


}