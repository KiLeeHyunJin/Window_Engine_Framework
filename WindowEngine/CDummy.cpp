#include "CDummy.h"
#include "CColliderComponent.h"
#include "CTransformComponent.h"
#include "CRigidbodyComponent.h"

#include "CCollisionManager.h"
#include "CInputManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"

#include "CActor.h"
#include "Utils.h"

namespace Framework
{
	void CDummy::BeginPlay()
	{
	}
	void CDummy::Release()
	{
	}
	bool CDummy::TickComponent()
	{
		CActor* owner = GetOwner();

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
		//const float TickComponentTime = GET_SINGLE(TIME).DeltaTime();
		const float movePower = speed * 5;
		CRigidbodyComponent* rigid = owner->GetComponent<CRigidbodyComponent>();
		Maths::Vector2 addForceDir;

		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::A))
		{
			addForceDir += Maths::Vector2::Left;
		}
		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::D))
		{
			addForceDir += Maths::Vector2::Right;
		}
		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::W))
		{
			addForceDir += Maths::Vector2::Up;
		}
		if (GET_SINGLE(INPUT).GetKeyPressed(eKeyCode::S))
		{
			addForceDir += Maths::Vector2::Down;
			//Object::Destroy(GetOwner());

		}
		if (addForceDir.HasValue())
		{
			addForceDir.Normalize();
			rigid->SetVelocity(addForceDir * movePower);
		}

		if (GET_SINGLE(INPUT).GetKeyDown(eKeyCode::Enter))
		{
			GET_SINGLE(EVENT).ChangeLayer(GetOwner(), (UINT)Enums::eLayerType::Particle);
		}
		return true;
	}

	void CDummy::Render(HDC hdc)
	{
		HBRUSH newBrush = CreateSolidBrush(RGB(m_colorFill.r, m_colorFill.g, m_colorFill.b));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

		CColliderComponent* coll = GetOwner()->GetComponent<CColliderComponent>();
		Maths::Vector2 pos = GetOwner()->GetPosition();
		Maths::Vector2 size = coll->GetSize();
		Utils::DrawRect(hdc, pos, size);

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
