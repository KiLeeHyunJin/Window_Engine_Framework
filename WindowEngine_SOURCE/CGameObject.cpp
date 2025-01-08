#pragma once
#include "CGameObject.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CTransformComponent.h"

namespace Framework
{
	CGameObject::CGameObject()
	{
		m_vecComponent.resize((int)Enums::eComponentType::Size);
		AddTransform();
	}

	CGameObject::~CGameObject()
	{
	}

	void CGameObject::Initialize()
	{
		for (CComponent* pCom : m_vecComponent)
		{
			if (pCom != nullptr)
			{
				pCom->Initialize();
			}
		}
	}

	void CGameObject::Tick()
	{
		for (CComponent* pCom : m_vecComponent)
		{
			if (pCom != nullptr)
			{
				pCom->Tick();
			}
		}
	}

	void CGameObject::LastTick()
	{
		for (CComponent* pCom : m_vecComponent)
		{
			if (pCom != nullptr)
			{
				pCom->LastTick();
			}
		}

	}
	
	void CGameObject::Render(HDC hdc) const
	{
		for (CComponent* pCom : m_vecComponent)
		{
			if (pCom != nullptr)
			{
				pCom->Render(hdc);
			}
		}
	}
	void CGameObject::Release()
	{
		for (CComponent* pCom : m_vecComponent)
		{
			if (pCom != nullptr)
			{
				pCom->Release();
			}
		}
	}

	void CGameObject::AddTransform()
	{
		AddComponent<CTransformComponent>();
	}
}