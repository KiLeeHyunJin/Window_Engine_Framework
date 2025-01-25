#pragma once
#include "CGameObject.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CTransformComponent.h"

namespace Framework
{
	CGameObject::CGameObject(Enums::eLayerType layerType) : m_eState(eState::Enable), m_eLayerType(layerType), m_pTransformComponent(nullptr)
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
		for (CComponent* pCom : m_listCustomComponents)
		{
			pCom->Initialize();
		}
	}

	void CGameObject::Dead()
	{
		m_eState = eState::Destory;
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
		for (CComponent* pCom : m_listCustomComponents) 
		{
			pCom->Tick();
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
		for (CComponent* pCom : m_listCustomComponents)
		{
			pCom->LastTick();
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
		for (CComponent* pCom : m_listCustomComponents)
		{
			pCom->Render(hdc);
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
		for (CComponent* pCom : m_listCustomComponents)
		{
			pCom->Release();
			delete pCom;
		}
		m_vecComponents.clear();
		m_vecComponents.clear();
	}

	void CGameObject::AddTransform()
	{
		if (m_pTransformComponent == nullptr)
		{
			m_pTransformComponent = AddComponent<CTransformComponent>();
		}
	}
}