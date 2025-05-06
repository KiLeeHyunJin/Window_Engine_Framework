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
		bool result = SUPER::LastTick();

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

	bool CTileActor::CheckCollisionLine(const CBoxColliderComponent* target, float& lineY)
	{
		if (m_pLine->GetTrigger()) //비활성화 타일일 경우 false
		{		return false;	}

		CActor* targetOwner = target->GetOwner();
		const Maths::Vector2 pos = targetOwner->GetPosition() + target->GetOffset();

		if (m_pLine->GetPositionY(pos.x, &lineY) == false)
		{		return false;	}

		if (lineY > pos.y) //선보다 위
		{		return false;	}

		//선 높이랑 플레이어 높이가 플레이어의 콜라이더 박스 높이의 20% 보다 크다면 충돌 인정 X 
		const float length = Maths::Abs(lineY - pos.y);
		const float targetSizeIgnoreLenth = target->GetSize().y * 0.12f;
		if (length > targetSizeIgnoreLenth)
		{		return false;	}

		return true;
	}


	void CTileActor::GetPositionY(float x, float& y)
	{
		if (m_pLine->GetPositionY(x, &y) == false)
		{
			y = 0;
		}
	}


}