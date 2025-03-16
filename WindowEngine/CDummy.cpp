#include "CDummy.h"
#include "CColliderComponent.h"
#include "CTransformComponent.h"
#include "CRigidbodyComponent.h"

#include "CCollisionManager.h"
#include "CInputManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"

#include "CGameObject.h"

namespace Framework
{
	void CDummy::Initialize()
	{
	}
	void CDummy::Release()
	{
	}
	void CDummy::Tick()
	{
		CGameObject* owner = GetOwner();

		/*CColliderComponent outColl;
		Ray ray;
		ray.origin = owner->GetTransformComponent()->GetPos();
		ray.direction = Maths::Vector2(0, 1);
		CColliderComponent* ownerColl = GetOwner()->GetComponent<CColliderComponent>();
		std::vector<CColliderComponent*> ignoreColl;
		ignoreColl.push_back(ownerColl);*/

		//bool state = CCollisionManager::Raycast(ray, outColl, ignoreColl);
		//if (state)
		//{
		//	m_colorFill = Color(0, 0, 255);
		//}
		//else
		//{
		//	m_colorFill = Color(255, 0, 255);

		//}

		const float speed = 20;
		//const float tickTime = TIME::DeltaTime();
		const float movePower = speed * 5;
		CRigidbodyComponent* rigid = owner->GetComponent<CRigidbodyComponent>();
		Maths::Vector2 addForceDir;

		if (INPUT::GetKeyPressed(eKeyCode::A))
		{
			addForceDir += Maths::Vector2::Left;
		}
		if (INPUT::GetKeyPressed(eKeyCode::D))
		{
			addForceDir += Maths::Vector2::Right;
		}
		if (INPUT::GetKeyPressed(eKeyCode::W))
		{
			addForceDir += Maths::Vector2::Up;
		}
		if (INPUT::GetKeyPressed(eKeyCode::S))
		{
			addForceDir += Maths::Vector2::Down;
			//Object::Destroy(GetOwner());

		}
		if (addForceDir.HasValue())
		{
			addForceDir.Normalize();
			rigid->SetVelocity(addForceDir * movePower);
		}

		if (INPUT::GetKeyDown(eKeyCode::Enter))
		{
			EVENT::ChangeLayer(GetOwner(), (UINT)Enums::eLayerType::Particle);
		}
	}

	void CDummy::Render(HDC hdc)
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

	void CDummy::OnCollisionEnter(CColliderComponent* other)
	{
		m_colorFill = Color(255, 0, 255);
	}
	void CDummy::OnCollisionStay(CColliderComponent* other)
	{
	}
	void CDummy::OnCollisionExit(CColliderComponent* other)
	{
		m_colorFill = Color(0, 0, 255);

	}

}
