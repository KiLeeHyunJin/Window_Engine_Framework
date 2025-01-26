#include "CPlayerInput.h"

#include "..\\WindowEngine_SOURCE\\CTimeManager.h"
#include "..\\WindowEngine_SOURCE\\CInputManager.h"

#include "CTransformComponent.h"
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
		float speed = 200;
		static float time = 0; 
		time += DELTATIME;
		if (time > 6)
		{
			//Object::Destroy(GetOwner());
		}
		CTransformComponent* tr = GetOwner()->GetComponent<CTransformComponent>();
		Maths::Vector2 pos = tr->GetPos();
		if (INPUT::GetKeyPressed(eKeyCode::Left))
		{
			pos.AddX(-speed * DELTATIME);
		}
		if (INPUT::GetKeyPressed(eKeyCode::Right))
		{
			pos.AddX(speed * DELTATIME);
		}
		if (INPUT::GetKeyPressed(eKeyCode::Up))
		{
			pos.AddY(-speed * DELTATIME);
		}
		if (INPUT::GetKeyPressed(eKeyCode::Down))
		{
			pos.AddY(speed * DELTATIME);
		}
		tr->SetPos(pos);
	}
	void CPlayerInput::LastTick()
	{
	}
	void CPlayerInput::Render(HDC hdc)
	{
	}
}