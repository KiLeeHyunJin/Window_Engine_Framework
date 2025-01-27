#include "CPlayerInput.h"

#include "..\\WindowEngine_SOURCE\\CTimeManager.h"
#include "..\\WindowEngine_SOURCE\\CInputManager.h"

#include "CTransformComponent.h"
#include "CRigidbodyComponent.h"

#include "CGameObject.h"
#include "CObject.h"
namespace Framework
{
	CPlayerInput::CPlayerInput()
	{
	}
	CPlayerInput::~CPlayerInput()
	{
	}
	void CPlayerInput::Initialize()
	{
	}
	void CPlayerInput::Release()
	{
	}
	void CPlayerInput::Tick()
	{
		const float speed = 200;
		const float tickTime = TIME::DeltaTime();
		const float movePower = speed * tickTime;

		CRigidbodyComponent* rigid = GetOwner()->GetComponent<CRigidbodyComponent>();
		Maths::Vector2 addForceDir;

		if (INPUT::GetKeyPressed(eKeyCode::Left))
		{
			addForceDir += Maths::Vector2::Left;
		}
		if (INPUT::GetKeyPressed(eKeyCode::Right))
		{
			addForceDir += Maths::Vector2::Right;
		}
		if (INPUT::GetKeyPressed(eKeyCode::Up))
		{
			addForceDir += Maths::Vector2::Up;
		}
		if (INPUT::GetKeyPressed(eKeyCode::Down))
		{
			addForceDir += Maths::Vector2::Down;
		}
		rigid->SetVelocity(addForceDir.Normalized() * movePower);

		//tr->SetPos(pos);
	}
	void CPlayerInput::LastTick()
	{
	}
	void CPlayerInput::Render(HDC hdc)
	{
	}
}