#include "CPlayerInput.h"

#include "..\\WindowEngine_SOURCE\\CTimeManager.h"
#include "..\\WindowEngine_SOURCE\\CInputManager.h"

#include "CTransformComponent.h"
#include "CGameObject.h"
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
		float speed = 200;

		CTransformComponent* tr = GetOwner()->GetComponent<CTransformComponent>();
		float x = tr->GetX();
		float y = tr->GetY();
		if (INPUT::GetKeyPressed(eKeyCode::Left))
		{
			x -= speed * DELTATIME;
		}
		if (INPUT::GetKeyPressed(eKeyCode::Right))
		{
			x += speed * DELTATIME;

		}
		if (INPUT::GetKeyPressed(eKeyCode::Up))
		{
			y -= speed * DELTATIME;
		}
		if (INPUT::GetKeyPressed(eKeyCode::Down))
		{
			y += speed * DELTATIME;
		}
		tr->SetPos(Maths::Vector2(x, y));
	}
	void CPlayerInput::LastTick()
	{
	}
	void CPlayerInput::Render(HDC hdc)
	{
	}
}