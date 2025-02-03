#include "CUIBase.h"

namespace Framework
{
	CUIBase::CUIBase()
	{
	}
	CUIBase::~CUIBase()
	{
	}

	void CUIBase::OnInitialize()
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
	void CUIBase::OnClear()
	{
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