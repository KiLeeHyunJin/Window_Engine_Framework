#pragma once
#include "CGameObject.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CTransformComponent.h"

namespace Framework
{
	CGameObject::CGameObject()
	{
		m_vecComponents.resize((int)Enums::eComponentType::Size);
		AddTransform();
	}

	CGameObject::~CGameObject()
	{
	}

	void CGameObject::Initialize()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Initialize();
			}
		}
	}

	void CGameObject::Tick()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Tick();
			}
		}
	}

	void CGameObject::LastTick()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->LastTick();
			}
		}

	}
	
	void CGameObject::Render(HDC hdc) const
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Render(hdc);
			}
		}
	}
	void CGameObject::Release()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Release();
				delete pCom;
			}
		}
		m_vecComponents.clear();
	}

	void CGameObject::AddTransform()
	{
		AddComponent<CTransformComponent>();
	}
}