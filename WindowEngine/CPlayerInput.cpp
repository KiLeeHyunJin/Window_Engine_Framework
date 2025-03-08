#include "CPlayerInput.h"

#include "..\\WindowEngine_SOURCE\\CTimeManager.h"
#include "..\\WindowEngine_SOURCE\\CInputManager.h"
#include "..\\WindowEngine_SOURCE\\CCollisionManager.h"

#include "CTransformComponent.h"
#include "CRigidbodyComponent.h"
#include "CColliderComponent.h"
#include "CRenderManager.h"
#include "Structs.h"
#include "CGameObject.h"
#include "CObject.h"
namespace Framework
{
	int CPlayerInput::temp = 0;

	CPlayerInput::CPlayerInput() : id(0)
	{
	}
	CPlayerInput::~CPlayerInput()
	{
	}
	void CPlayerInput::Initialize()
	{
		id = temp++;
	}
	void CPlayerInput::Release()
	{
	}
	void CPlayerInput::Tick()
	{
		if (id >= 1)
		{
			return;
		}

		CGameObject* owner = GetOwner();

		CColliderComponent outColl;
		Ray ray;
		ray.origin = owner->GetTransformComponent()->GetPos();
		ray.direction = Maths::Vector2(0, 1);
		CColliderComponent* ownerColl = GetOwner()->GetComponent<CColliderComponent>();
		std::vector<CColliderComponent*> ignoreColl;
		ignoreColl.push_back(ownerColl);

		bool state = CCollisionManager::Raycast(ray, outColl, ignoreColl);
		if (state)
		{
			m_colorFill = Color(0, 0, 255);
		}
		else
		{
			m_colorFill = Color(255, 0, 255);

		}

		const float speed = 20;
		//const float tickTime = TIME::DeltaTime();
		const float movePower = speed * 10;
		CRigidbodyComponent* rigid = owner->GetComponent<CRigidbodyComponent>();
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
			Object::Destroy(GetOwner());

		}
		if (addForceDir.HasValue())
		{
			addForceDir.Normalize();
			rigid->SetVelocity(addForceDir * movePower);
		}
		if (INPUT::GetKeyDown(eKeyCode::Q))
		{
			Maths::Vector2 pos;
			pos.x = ray.origin.x - 50;
			pos.y = 0;
			Maths::Vector2 size;
			size.x = 50;
			size.y = 50;
			const auto& list = CCollisionManager::GetCollisionCollider(pos, size);
			if (list.size() != 0)
			{
				int a = 1;
			}
		}
	}
	void CPlayerInput::LastTick()
	{
	}
	void CPlayerInput::Render(HDC hdc)
	{
		HBRUSH newBrush = CreateSolidBrush(RGB(m_colorFill.r, m_colorFill.g, m_colorFill.b));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

		CColliderComponent* coll = GetOwner()->GetComponent<CColliderComponent>();
		Maths::Vector2 pos = GetOwner()->GetTransformComponent()->GetPos();
		Maths::Vector2 size = coll->GetSize();
		CRenderManager::DrawRectangle(hdc, pos, size);

		MoveToEx(hdc, 
			(INT)pos.x, 
			(INT)pos.y, nullptr);
		LineTo(hdc, 
			(INT)pos.x,
			(INT)pos.y + 100);

		(HBRUSH)SelectObject(hdc, oldBrush);
		DeleteObject(newBrush);
	}
	void CPlayerInput::OnCollisionEnter(CColliderComponent* other)
	{
	}
	void CPlayerInput::OnCollisionStay(CColliderComponent* other)
	{
	}
	void CPlayerInput::OnCollisionExit(CColliderComponent* other)
	{
	}
}