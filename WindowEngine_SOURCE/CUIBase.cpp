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
	CUIBase::CUIBase() :
		m_bEnable(false), m_bFullScreen(false), m_bDraggable(false), m_bIsDrag(false), m_bWorldObject(false), m_bChangeHierarchy(false), m_bFocusOn(false),
		m_bCurMouseDown(false), m_bCurMouseOn(false), m_bPrevMouseOn(false), m_bPrevMouseDown(false),
		m_pParent(nullptr), m_eType(Enums::eUIType::Button), m_iIndex(-1), m_eLayerType(Enums::eUILayer::None),
		m_vecRenderPos(Maths::Vector2::Zero)
	{
	}
	CUIBase::~CUIBase()						{	}

	void CUIBase::OnInitialize()
	{
		m_vecPos = Maths::Vector2(150, 100);
		m_vecSize = Maths::Vector2(150, 150);

		CButton* left = new CButton();
		left->SetLocalPosition(Maths::Vector2(-70, 0));
		left->SetScale(Maths::Vector2(50, 50));
		left->SetChangeHierarchy(true);
		AddChildUI(left);

		/*	CButton* right = new CButton();
			right->SetLocalPosition(Maths::Vector2( 70, 0));
			right->SetScale(Maths::Vector2(50, 50));
			right->SetChangeHierarchy(true);
			AddChildUI(right);*/
	}

	void CUIBase::OnRelease()				{	}

	void CUIBase::OnActive()				{	}
	void CUIBase::OnInActive()				{	}	
	void CUIBase::OnTickComponent()			{	}
	void CUIBase::OnLastTickComponent()		{	}

	void CUIBase::OnRender(HDC hdc) const	{ Utils::DrawRect(hdc, m_vecRenderPos, m_vecSize); }

	void CUIBase::OnClear()					{	}

	void CUIBase::OnEnter()					{	}
	void CUIBase::OnExit()					{	}
	void CUIBase::OnDown()					{	}
	void CUIBase::OnUp()					{	}
	void CUIBase::OnClick()					{	}


	void CUIBase::AddChildUI(CUIBase* pChildUI)
	{
		pChildUI->SetParent(this);
		//pChildUI->SetDrag(m_bDraggable);
		pChildUI->SetChangeHierarchy(m_bChangeHierarchy);
		pChildUI->SetWorldObject(m_bWorldObject);
		m_vecChilds.push_back(pChildUI);
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
		const Maths::Vector2 halfSize = GetScale() * 0.5f;
		const auto& checkPos = GET_SINGLE(INPUT).GetMousePosition();

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
		Maths::Vector2 vecAbsolutePos = GetLocalPosition();
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
		OnTickComponent();
		UpdatePosition();
		MouseOnCheck();
		for (auto& child : GetChilds())
		{
			child->Tick();
		}
	}
	
	void CUIBase::LastTick()
	{
		OnLastTickComponent();
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
		if (GetFocus() == false)
		{
			m_bFocusOn = true;
			OnEnter();
		}
	}

	void CUIBase::Over()
	{
		if (GetDragging())
		{
			Maths::Vector2 mousePos = GET_SINGLE(INPUT).GetMousePosition();
			Maths::Vector2 vecDiff = mousePos - m_vecDragStartPos;

			m_vecPos = m_vecPos + vecDiff;
			m_vecDragStartPos = mousePos;
		}
	}

	void CUIBase::Exit()
	{
		if (GET_SINGLE(INPUT).GetKeyUp(eKeyCode::LBUTTON))
		{
			m_bPrevMouseDown = false;
		}
		if (GetFocus())
		{
			m_bFocusOn = false;
			if (GetDragging())
			{
				m_bIsDrag = false;
			}
			if (GetCurOn())
			{
				m_bCurMouseOn = false;
			}
			OnExit();
		}

	}

	void CUIBase::Down()
	{
		if (m_bPrevMouseDown == false)
		{
			m_bPrevMouseDown = true;
		}
		if (m_bDraggable)
		{
			m_vecDragStartPos = GET_SINGLE(INPUT).GetMousePosition();
			m_bIsDrag = true;
		}
		if (m_bChangeHierarchy)
		{
			GET_SINGLE(UI).SetLastSibling(this);
		}
		OnDown();
	}

	void CUIBase::Up()
	{
		if (m_bIsDrag)
		{
			m_bIsDrag = false;
			m_vecRenderPos = GET_SINGLE(INPUT).GetMousePosition();
		}
		if (m_bPrevMouseDown)
		{
			m_bPrevMouseDown = false;
			OnClick();
		}

		OnUp();

	}
}