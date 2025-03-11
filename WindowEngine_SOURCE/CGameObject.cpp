#pragma once
#include "CGameObject.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"

#include "CTransformComponent.h"
#include "CRigidbodyComponent.h"

namespace Framework
{
	CGameObject::CGameObject(Enums::eLayerType layerType) :
		m_eState(eState::Enable), m_eLayerType(layerType), 
		m_bReserveDelete(false), m_bSafeToDelete(false), m_bDontDestroy(false),
		m_pTransform(new CTransformComponent)
	{
		m_vecComponents.resize((int)Enums::eComponentType::Size, nullptr);
		m_vecComponents[(UINT)Enums::eComponentType::Transform] = m_pTransform;
	}

	CGameObject::~CGameObject()
	{	}
	
	void CGameObject::Initialize()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Initialize();
			}
		}
		for (CComponent* pCom : m_vecCustomComponents)
		{
			pCom->Initialize();
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
		for (CComponent* pCom : m_vecCustomComponents)
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
		for (CComponent* pCom : m_vecCustomComponents)
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
		for (CComponent* pCom : m_vecCustomComponents)
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
		for (CComponent* pCom : m_vecCustomComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Release();
				delete pCom;
			}
		}
		m_vecComponents.clear();
		m_vecComponents.clear();
	}

	void CGameObject::ChangeLayer(const Enums::eLayerType layerType)
	{
		if (layerType != m_eLayerType)
		{
			EVENT::ChangeLayer(this, layerType);
		}
	}

	//void CGameObject::AddTransform()
	//{
	//	if (m_pTransform == nullptr)
	//	{
	//		m_pTransform = AddComponent<CTransformComponent>();
	//	}
	//}
}