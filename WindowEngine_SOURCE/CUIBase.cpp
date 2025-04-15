#include "CUIBase.h"
#include "CButton.h"

#include "CInputManager.h"
#include "CUIManager.h"
#include "CRenderManager.h"

#include "CRenderer.h"
#include "CCameraComponent.h"
#include "Utils.h"

namespace Framework
{
	CUIBase::CUIBase()						{	}
	CUIBase::~CUIBase()						{	}

	void CUIBase::OnInitialize()
	{
		m_vecSize = Maths::Vector2(150, 150);

		CButton* left = new CButton();
		left->SetLocalPosition(Maths::Vector2(-70, 0));
		left->SetScale(Maths::Vector2(50, 50));
		left->SetChangeHierarchy(true);
		left->SetDraggable(true);
		AddChildUI(left);

	}

	void CUIBase::OnRender(HDC hdc) const	{ Utils::DrawRect(hdc, m_vecRenderPos, m_vecSize); }



	void CUIBase::AddChildUI(CUIBase* pChildUI)
	{
		pChildUI->SetParent(this);
		pChildUI->SetChangeHierarchy(m_bChangeHierarchy);
		pChildUI->SetWorldObject(m_bWorldObject);
		m_vecChilds.push_back(pChildUI);
	}

	void CUIBase::RemoveChildUI(CUIBase* pChildUI)
	{
		auto iter = std::find(m_vecChilds.cbegin(), m_vecChilds.cend(), pChildUI);
		if (iter != m_vecChilds.cend())
		{
			CUIBase* pUI = *iter;
			pUI->SetIndex(-1);
			iter = m_vecChilds.erase(iter);
		}
		assert(1);
		/// 자식 어떻게 할지와 재 호출 시 구조를 어떻게 조정할지 
	}

	void CUIBase::UpdatePosition()
	{
		Maths::Vector2 vecAbsolutePos = m_vecPos;
		if (m_pParent != nullptr)
		{
			vecAbsolutePos = vecAbsolutePos + (m_pParent->GetLocalPosition());
		}
		CCameraComponent* cam = Renderer::CRenderer::GetMainCamera();

		const bool state = m_bWorldObject && cam != nullptr;
		if (state)
		{
			m_vecRenderPos = cam->CaluatePosition(vecAbsolutePos);
		}
		else
		{
			m_vecRenderPos = vecAbsolutePos;
		}
	}



	void CUIBase::Initialize()
	{
		OnExit();
		OnInitialize();
		for (auto& child : GetChilds())
		{
			child->Initialize();
		}
	}

	void CUIBase::Tick()
	{
		OnTick();
		UpdatePosition();
		MouseInRect();
		for (auto& child : GetChilds())
		{
			child->Tick();
		}

	}
	
	void CUIBase::LastTick()
	{
		OnLastTick();
		for (auto& child : GetChilds())
		{
			child->LastTick();
		}
	}
	
	void CUIBase::Release()
	{
		for (auto& child : GetChilds())
		{
			child->Release();
			delete child;
		}
		m_vecChilds.clear();
		OnRelease();
	}

	void CUIBase::Render(HDC hdc) const
	{
		OnRender(hdc);
		for (auto& child : GetChilds())
		{
			child->Render(hdc);
		}
	}
	
	void CUIBase::Active()
	{
		OnActive();
		for (auto& child : GetChilds())
		{
			child->Active();
		}
	}
	
	void CUIBase::InActive()
	{
		OnInActive();
		for (auto& child : GetChilds())
		{
			child->InActive();
		}
	}

	RECT CUIBase::GetRect()
	{
		const Maths::Vector2 half = m_vecSize * 0.5f;
		RECT rect = {
			(LONG)(m_vecRenderPos.x - half.x),
			(LONG)(m_vecRenderPos.y - half.y),
			(LONG)(m_vecRenderPos.x + half.x),
			(LONG)(m_vecRenderPos.y + half.y) };
		return rect;
	}

	bool CUIBase::MouseInRect()
	{
		const Maths::Vector2 halfSize = GetScale() * 0.5f;
		const auto& checkPos = GET_SINGLE(INPUT).GetMousePosition();

		if (m_vecRenderPos.x - halfSize.x <= checkPos.x &&
			m_vecRenderPos.x + halfSize.x >= checkPos.x)
		{
			if (m_vecRenderPos.y - halfSize.y <= checkPos.y &&
				m_vecRenderPos.y + halfSize.y >= checkPos.y)
			{
				m_bCurMouseOn = true;
				return true;
			}
		}
		m_bCurMouseOn = false;
		return true;
	}


	void CUIBase::Clear()
	{
		for (auto& child : GetChilds())
		{
			child->Clear();
		}
		OnClear();
	}

	void CUIBase::Enter()
	{
		if (m_eUIState == eUIState::Default)
		{
			SetState(eUIState::Hovered);
		}
		else if(m_eUIState == eUIState::Pressed)
		{
			if (m_bDraggable)
			{
				const Maths::Vector2& currMousePos	= GET_SINGLE(INPUT).GetMousePosition();	//마우스 위치
				Maths::Vector2 vecDiffMousePos		= currMousePos - m_vecPrevMousePos;		//이전 마우스와 현재 마우스 위치 차이
				m_vecPrevMousePos					= currMousePos;							//현재 마우스 위치 저장

				m_vecPos = m_vecPos + vecDiffMousePos;										//마우스 이동한 만큼 합쳐서 위치에 저장
			}
		}
		OnEnter();
	}

	void CUIBase::Exit()
	{
		//if (GET_SINGLE(INPUT).GetKeyUp(eKeyCode::LBUTTON))
		//{
		//	//m_bPrevMouseDown = false;
		//}

		if (m_eUIState != eUIState::Default)
		{
			SetState(eUIState::Default);
			m_bCurMouseOn = false;
			OnExit();
		}

	}

	void CUIBase::Down()
	{
		if (m_eUIState != eUIState::Pressed)
		{
			SetState(eUIState::Pressed);
			OnDown();

			if (m_bDraggable)
			{
				m_vecDragStartPos = m_vecPos;
				m_vecPrevMousePos = GET_SINGLE(INPUT).GetMousePosition();
			}
			if (m_bChangeHierarchy)
			{
				GET_SINGLE(UI).SetLastSibling(this);
			}
		}
	}

	void CUIBase::Up()
	{
		if (m_eUIState == eUIState::Pressed)
		{
			if (m_bDraggable)
			{
				float sqrLength = (m_vecDragStartPos - m_vecPos).SqrLength();
				if (sqrLength > DRAG_ALLOWABLE_RANGE)
				{
					m_bPrevDrag = true;
				}
				else
				{
					m_bPrevDrag = false;
				}
			}
			

			SetState(eUIState::Hovered);

			OnUp();
		}

	}
}