#pragma once
#include "CGameObject.h"
#include "CRenderer.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"

#include "CTransformComponent.h"
#include "CRigidbodyComponent.h"

namespace Framework
{
	CGameObject::CGameObject(UINT layerType) :
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

	bool CGameObject::Tick()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->Tick();
			}
		}

		bool state = true;
		for (CComponent* pCom : m_vecCustomComponents)
		{
			const bool currentComResult = pCom->Tick();
			if (state && currentComResult == false)
			{
				state = false;
			}
		}
		return state;
	}

	bool CGameObject::LastTick()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->LastTick();
			}
		}

		bool state = true;

		for (CComponent* pCom : m_vecCustomComponents)
		{
			const bool currentComResult = pCom->LastTick();
			if (state && currentComResult == false)
			{
				state = false;
			}
		}
		return state;
	}
	
	void CGameObject::Render(HDC hdc) const
	{
		if (RenderCheck() == false) //화면 안에 없으면 렌더 실행 취소
		{	return;		}

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
	bool CGameObject::RenderCheck() const
	{
		Vector2 pos = m_pTransform->GetPos();
		const CCameraComponent* mainCam = Renderer::CRenderer::GetMainCamera();
		if (mainCam != nullptr)
		{
			pos = mainCam->CaluatePosition(pos);
			const bool result = mainCam->ScreenInCheck(pos, m_pTransform->m_vecScale); //화면 안에 있는지 결과를 반환
			return result;
		}
		return true;
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

	void CGameObject::ChangeLayer(const UINT layerType)
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