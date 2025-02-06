#include "CUIBase.h"
#include "CButton.h"
#include "CInputManager.h"

namespace Framework
{
	CUIBase::CUIBase() :
		m_bEnable(false), m_bFullScreen(false), m_bDragable(false),
		m_bCurMouseDown(false), m_bCurMouseOn(false), m_bPrevMouseOn(false), m_bPrevMouseDown(false),
		m_pParent(nullptr), m_eType(Enums::eUIType::Button), m_iIndex(-1)
	{
	}
	CUIBase::~CUIBase()
	{
		for (auto& child : m_vecChilds)
		{
			delete child;
		}
		m_vecChilds.clear();
	}

	void CUIBase::OnInitialize()
	{
		m_vecPos = Maths::Vector2(150, 100);
		m_vecSize = Maths::Vector2(150, 150);

		CButton* left = new CButton();
		left->SetPosition(Maths::Vector2(100, 100));
		left->SetScale(Maths::Vector2(50, 50));

		CButton* right = new CButton();
		right->SetPosition(Maths::Vector2(200, 100));
		right->SetScale(Maths::Vector2(50, 50));

		m_vecChilds.push_back(left);
		m_vecChilds.push_back(right);


	}

	void CUIBase::OnRelease()
	{
	}

	void CUIBase::OnActive()
	{
	}
	void CUIBase::OnInActive()
	{
	}
	void CUIBase::OnTick()
	{
	}
	void CUIBase::OnLastTick()
	{
	}
	void CUIBase::OnRender(HDC hdc)
	{
		Rectangle(hdc,
			m_vecPos.x - (m_vecSize.x * 0.5f), m_vecPos.y - (m_vecSize.y * 0.5f),
			m_vecPos.x + (m_vecSize.x * 0.5f), m_vecPos.y + (m_vecSize.y * 0.5f));

	}
	void CUIBase::OnClear()
	{
	}

	void CUIBase::OnOver()
	{
	}

	void CUIBase::OnOut()
	{
	}

	void CUIBase::OnDown()
	{
	}

	void CUIBase::OnUp()
	{
	}

	void CUIBase::OnClick()
	{
	}

	void CUIBase::MouseOnCheck()
	{
		m_bPrevMouseOn = m_bCurMouseOn;

		const Maths::Vector2 halfSize = m_vecSize * 0.5f;
		const auto& checkPos = INPUT::GetMousePosition();

		m_bCurMouseOn =
			m_vecPos.x - halfSize.x <= checkPos.x && 
			m_vecPos.x + halfSize.x >= checkPos.x &&
			m_vecPos.y - halfSize.y <= checkPos.y && 
			m_vecPos.y + halfSize.y >= checkPos.y;
	}

	void CUIBase::Initialize()
	{
		OnInitialize();
		for (auto& child : m_vecChilds)
		{
			OnInitialize();
		}
	}

	void CUIBase::Tick()
	{
		OnTick();
		MouseOnCheck();
		for (auto& child : m_vecChilds)
		{
			child->OnTick();
			child->MouseOnCheck();
		}
	}
	
	void CUIBase::LastTick()
	{
		OnLastTick();
		for (auto& child : m_vecChilds)
		{
			child->OnLastTick();
		}
	}
	
	void CUIBase::Release()
	{
		for (auto& child : m_vecChilds)
		{
			child->Release();
		}
		Release();
	}

	void CUIBase::Render(HDC hdc)
	{
		OnRender(hdc);
		for (auto& child : m_vecChilds)
		{
			child->OnRender(hdc);
		}
	}
	
	void CUIBase::Active()
	{
		OnActive();
		for (auto& child : m_vecChilds)
		{
			child->OnActive();
		}
	}
	
	void CUIBase::InActive()
	{
		OnInActive();
		for (auto& child : m_vecChilds)
		{
			child->OnInActive();
		}
	}
	void CUIBase::Clear()
	{
		for (auto& child : m_vecChilds)
		{
			child->Clear();
		}
		Clear();
	}
}