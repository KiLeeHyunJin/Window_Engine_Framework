#include "CUIBase.h"
#include "CButton.h"

#include "CInputManager.h"
#include "CUIManager.h"
#include "CRenderManager.h"

#include "CRenderer.h"
#include "CCameraComponent.h"

namespace Framework
{
	CUIBase::CUIBase() :
		m_bEnable(false), m_bFullScreen(false), m_bDraggable(false), m_bIsDrag(false), m_bWorldObject(false), m_bChangeHierarchy(false), m_bFocusOn(false),
		m_bCurMouseDown(false), m_bCurMouseOn(false), m_bPrevMouseOn(false), m_bPrevMouseDown(false),
		m_pParent(nullptr), m_eType(Enums::eUIType::Button), m_iIndex(-1),
		m_vecRenderPos(Maths::Vector2::Zero)
	{
	}
	CUIBase::~CUIBase()				{	}

	void CUIBase::OnInitialize()
	{
		m_vecPos = Maths::Vector2(150, 100);
		m_vecSize = Maths::Vector2(150, 150);

		CButton* left = new CButton();
		left->SetLocalPosition(Maths::Vector2( -70, 0));
		left->SetScale(Maths::Vector2(50, 50));
		left->SetChangeHierarchy(true);
		AddChildUI(left);

	/*	CButton* right = new CButton();
		right->SetLocalPosition(Maths::Vector2( 70, 0));
		right->SetScale(Maths::Vector2(50, 50));
		right->SetChangeHierarchy(true);
		AddChildUI(right);*/
	}

	void CUIBase::OnRelease()		{	}
	void CUIBase::OnActive()		{	}
	void CUIBase::OnInActive()		{	}
	void CUIBase::OnTick()			{	}
	void CUIBase::OnLastTick()		{	}

	void CUIBase::OnRender(HDC hdc) const 
	{ 
		RENDER::DrawRectangle(hdc, m_vecRenderPos, m_vecSize); 
	}
	void CUIBase::OnClear()			{	}

	void CUIBase::OnEnter()			{	}
	void CUIBase::OnExit()			{	}
	void CUIBase::OnDown()			{	}
	void CUIBase::OnUp()			{	}
	void CUIBase::OnClick()			{	}

	void CUIBase::AddChildUI(CUIBase* pChildUI)
	{
		m_vecChilds.push_back(pChildUI);
		pChildUI->SetParent(this);
		pChildUI->SetDrag(m_bDraggable);
		pChildUI->m_bWorldObject = m_bWorldObject;
	}

	void CUIBase::RemoveChildUI(CUIBase* pChildUI)
	{
		auto iter = std::find(m_vecChilds.cbegin(), m_vecChilds.cend(), pChildUI);
		if (iter != m_vecChilds.cend())
		{
			m_vecChilds.erase(iter);
		}
		assert(1);
		/// 자식 어떻게 할지와 재 호출 시 구조를 어떻게 조정할지 
	}

	void CUIBase::MouseOnCheck()
	{
		//m_bPrevMouseOn = m_bCurMouseOn;

		const Maths::Vector2 halfSize = m_vecSize * 0.5f;
		const auto& checkPos = INPUT::GetMousePosition();

		if (m_vecRenderPos.x - halfSize.x <= checkPos.x &&
			m_vecRenderPos.x + halfSize.x >= checkPos.x)
		{
			if (m_vecRenderPos.y - halfSize.y <= checkPos.y &&
				m_vecRenderPos.y + halfSize.y >= checkPos.y)
			{
				m_bCurMouseOn = true;
				return;
			}
		}
		m_bCurMouseOn = false;
	}

	void CUIBase::UpdatePosition()
	{
		Maths::Vector2 m_vecAbsolutePos;
		m_vecAbsolutePos = m_vecPos;
		if (m_pParent != nullptr)
		{
			m_vecAbsolutePos = m_vecAbsolutePos + (m_pParent->m_vecPos);
		}

		m_vecRenderPos = m_bWorldObject ?
			m_vecAbsolutePos :
			Renderer::CRenderer::GetMainCamera()->CaluatePosition(m_vecAbsolutePos);
	}



	void CUIBase::Initialize()
	{
		OnExit();
		OnInitialize();
		for (auto& child : m_vecChilds)
		{
			child->Initialize();
		}
	}

	void CUIBase::Tick()
	{
		OnTick();
		UpdatePosition();
		MouseOnCheck();
		for (auto& child : m_vecChilds)
		{
			child->Tick();
		}
	}
	
	void CUIBase::LastTick()
	{
		OnLastTick();
		for (auto& child : m_vecChilds)
		{
			child->LastTick();
		}
	}
	
	void CUIBase::Release()
	{
		for (auto& child : m_vecChilds)
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
		for (auto& child : m_vecChilds)
		{
			child->Render(hdc);
		}
	}
	
	void CUIBase::Active()
	{
		OnActive();
		for (auto& child : m_vecChilds)
		{
			child->Active();
		}
	}
	
	void CUIBase::InActive()
	{
		OnInActive();
		for (auto& child : m_vecChilds)
		{
			child->InActive();
		}
	}
	void CUIBase::Clear()
	{
		for (auto& child : m_vecChilds)
		{
			child->Clear();
		}
		OnClear();
	}

	void CUIBase::Enter()
	{
		if (m_bFocusOn == false)
		{
			m_bFocusOn = true;
			OnEnter();
		}
	}

	void CUIBase::Over()
	{
		Enter();

		if (m_bIsDrag)
		{
			Maths::Vector2 mousePos = INPUT::GetMousePosition();
			Maths::Vector2 vecDiff = mousePos - m_vecDragStartPos;

			m_vecPos = m_vecPos + vecDiff;
			m_vecDragStartPos = mousePos;
		}
	}

	void CUIBase::Exit()
	{
		if (m_bFocusOn)
		{
			m_bFocusOn = false;
			if (m_bIsDrag)
			{
				m_bIsDrag = false;
			}
			OnExit();
		}
		if (INPUT::GetKeyUp(eKeyCode::LBUTTON))
		{
			m_bPrevMouseDown = false;
		}
	}

	void CUIBase::Down()
	{
		OnDown();
		m_bPrevMouseDown = true;
		if (m_bDraggable)
		{
			m_vecDragStartPos = INPUT::GetMousePosition();
			m_bIsDrag = true;
		}
		if (m_bChangeHierarchy)
		{
			UI::SetLastSibling(this);
		}

	}

	void CUIBase::Up()
	{
		OnUp();
		if (m_bPrevMouseDown)
		{
			OnClick();
			m_bPrevMouseDown = false;
		}
		if (m_bIsDrag)
		{
			m_bIsDrag = false;
			m_vecRenderPos = INPUT::GetMousePosition();
		}
	}
}