#include "CUIBase.h"
#include "CButton.h"
namespace Framework
{
	CUIBase::CUIBase() :
		m_bEnable(false), m_bFullScreen(false), m_bMouseOn(false), m_bDragable(false),
		m_pParent(nullptr), m_eType(Enums::eUIType::Button), m_iIndex(0)
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
		CButton* left = new CButton();
		left->SetPosition(Maths::Vector2(100, 100));
		left->SetScale(Maths::Vector2(50, 50));

		CButton* right = new CButton();
		right->SetPosition(Maths::Vector2(200, 100));
		right->SetScale(Maths::Vector2(50, 50));

		m_vecChilds.push_back(left);
		m_vecChilds.push_back(right);

		for (auto& child : m_vecChilds)
		{
			child->OnInitialize();
		}
	}

	void CUIBase::OnRelease()
	{
		for (auto& child : m_vecChilds)
		{
			child->OnRelease();
		}
	}

	void CUIBase::OnActive()
	{
		for (auto& child : m_vecChilds)
		{
			child->OnActive();
		}
	}
	void CUIBase::OnInActive()
	{
		for (auto& child : m_vecChilds)
		{
			child->OnInActive();
		}
	}
	void CUIBase::OnTick()
	{
		for (auto& child : m_vecChilds)
		{
			child->OnTick();
		}
	}
	void CUIBase::OnLastTick()
	{
		for (auto& child : m_vecChilds)
		{
			child->OnLastTick();
		}
	}
	void CUIBase::OnRender(HDC hdc)
	{
		Rectangle(hdc,
			m_vecPos.x - (m_vecSize.x * 0.5f), m_vecPos.y - (m_vecSize.y * 0.5f),
			m_vecPos.x + (m_vecSize.x * 0.5f), m_vecPos.y + (m_vecSize.y * 0.5f));

		for (auto& child : m_vecChilds)
		{
			child->Render(hdc);
		}
	}
	void CUIBase::OnClear()
	{
		for (auto& child : m_vecChilds)
		{
			child->OnClear();
		}
	}

	void CUIBase::Initialize()
	{
		OnInitialize();
	}

	void CUIBase::Tick()
	{
		OnTick();
	}
	
	void CUIBase::LastTick()
	{
		OnLastTick();
	}
	
	void CUIBase::Release()
	{
		OnClear();
	}

	void CUIBase::Render(HDC hdc)
	{
		OnRender(hdc);
	}
	
	void CUIBase::Active()
	{
		OnActive();
	}
	
	void CUIBase::InActive()
	{
		OnInActive();
	}
}