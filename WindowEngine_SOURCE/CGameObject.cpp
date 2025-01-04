#pragma once
#include "CGameObject.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CTransform.h"
namespace Framework
{
	CGameObject::CGameObject()
	{
		AddTransform();
	}

	CGameObject::~CGameObject()
	{
	}

	void CGameObject::Initialize()
	{
		for (CComponent* pCom : m_vecComponent)
		{
			pCom->Initialize();
		}
	}

	void CGameObject::Tick()
	{
		for (CComponent* pCom : m_vecComponent)
		{
			pCom->Tick();
		}
		float speed = 200;
		CTransform* tr = GetComponent<CTransform>();
		float x = tr->GetX();
		float y = tr->GetY();
		if (INPUT::GetKeyPressed(eKeyCode::Left))
		{
			x -= speed * DELTATIME;
		}
		if (INPUT::GetKeyPressed(eKeyCode::Right))
		{
			x += speed * DELTATIME;

		}
		if (INPUT::GetKeyPressed(eKeyCode::Up))
		{
			y -= speed * DELTATIME;
		}
		if (INPUT::GetKeyPressed(eKeyCode::Down))
		{
			y += speed * DELTATIME;
		}
		tr->SetPos(Vector2(x,y));
	}

	void CGameObject::LastTick()
	{
		for (CComponent* pCom : m_vecComponent)
		{
			pCom->LastTick();
		}

	}
	
	void CGameObject::Render(HDC hdc) const
	{
		for (CComponent* pCom : m_vecComponent)
		{
			pCom->Render(hdc);
		}
	}
	void CGameObject::Release()
	{
		for (CComponent* pCom : m_vecComponent)
		{
			pCom->Release();
		}
	}

	void CGameObject::AddTransform()
	{
		AddComponent<CTransform>();
	}
}