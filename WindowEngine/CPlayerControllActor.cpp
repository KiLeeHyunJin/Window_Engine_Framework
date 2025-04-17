#include "CPlayerControllActor.h"
#include "CInputManager.h"
#include "CRigidbodyComponent.h"
#include "CColliderComponent.h"
namespace Framework
{
	CPlayerControllActor::CPlayerControllActor(UINT layer) :CActor(layer)
	{
	}
	void CPlayerControllActor::BeginPlay()
	{
		SUPER::BeginPlay();
	}
	void CPlayerControllActor::Release()
	{
		SUPER::Release();
	}
	bool CPlayerControllActor::Tick()
	{
		SUPER::Tick();
		const float speed = 20;
		//const float TickComponentTime = GET_SINGLE(TIME).DeltaTime();
		const float movePower = speed * 5;
		CRigidbodyComponent* rigid = GetComponent<CRigidbodyComponent>();
		if (rigid == nullptr)
		{		return true;		}
		Maths::Vector2 addForceDir;

		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::Left))
		{
			addForceDir += Maths::Vector2::Left;
		}
		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::Right))
		{
			addForceDir += Maths::Vector2::Right;
		}
		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::Up))
		{
			addForceDir += Maths::Vector2::Up;
		}
		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::Down))
		{
			addForceDir += Maths::Vector2::Down;
			//Object::Destroy(GetOwner());

		}
		if (addForceDir.HasValue())
		{
			addForceDir.Normalize();
			rigid->SetVelocity(addForceDir * movePower);
		}
		return true;
	}
	bool CPlayerControllActor::LastTick()
	{
		SUPER::LastTick();

		return true;
	}
	void CPlayerControllActor::Render(HDC hdc) const
	{
		SUPER::Render(hdc);

		//wchar_t str[50] = L"";
		//swprintf_s(str, 50, L"Ãæµ¹ : %d", (int)(collChecking));
		//int len = (int)wcsnlen_s(str, 50);

		//const Maths::Vector2 resolution = GET_SINGLE(RENDER).GetResolution();// - Maths::Vector2(100, 70);
		//TextOut(hdc, (static_cast<INT>(resolution.x - 130)), 140, str, len);

	}
	void CPlayerControllActor::OnCollisionEnter(CColliderComponent* other)
	{
		collChecking = other->GetColliderID();

	}
	void CPlayerControllActor::OnCollisionStay(CColliderComponent* other)
	{
	}
	void CPlayerControllActor::OnCollisionExit(CColliderComponent* other)
	{
		collChecking = UINT32_MAX;
	}
}