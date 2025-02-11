#include "CommonInclude.h"
#include "CBoxColliderComponent.h"
#include "CTransformComponent.h"
#include "CRenderer.h"
#include "CGameObject.h"

namespace Framework
{

	CBoxColliderComponent::CBoxColliderComponent() :
		CColliderComponent(eColliderType::Box)
	{
		 m_vecSize = (Maths::Vector2(50,50));
	}

	CBoxColliderComponent::~CBoxColliderComponent()
	{
	}

	void CBoxColliderComponent::Initialize()
	{
	}

	void CBoxColliderComponent::Release()
	{
	}

	void CBoxColliderComponent::Tick()
	{
	}

	void CBoxColliderComponent::LastTick()
	{
	}

	void CBoxColliderComponent::Render(HDC hdc)
	{
		const CTransformComponent* pTr = GetOwner()->GetTransformComponent();
		Maths::Vector2 pos = pTr->GetPos();
		CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
		if (pCam != nullptr)
		{
			pos = pCam->CaluatePosition(pos);
		}
		const Maths::Vector2 offsetPos = pos + m_vecOffset;

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc,transparentBrush);

		HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		const float sizeX = m_vecSize.x * 0.5f;
		const float sizeY = m_vecSize.y * 0.5f;

		Rectangle(hdc, 
			(INT)(offsetPos.x - sizeX), 
			(INT)(offsetPos.y - sizeY), 
			(INT)(offsetPos.x + sizeX), 
			(INT)(offsetPos.y + sizeY));

		transparentBrush = (HBRUSH)SelectObject(hdc, oldBrush);
		pen = (HPEN)SelectObject(hdc, oldPen);

		DeleteObject(pen);
	}

}
