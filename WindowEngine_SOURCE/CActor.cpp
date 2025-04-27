#pragma once
#include "CActor.h"
#include "CRenderer.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"

#include "CTransformComponent.h"
#include "CRigidbodyComponent.h"
namespace Framework
{
	CActor::CActor(UINT layerType) :
		m_eState(eState::Enable), m_eLayerType(layerType), m_uiID(0),
		m_bReserveDelete(false), m_bSafeToDelete(false), m_bDontDestroy(false),m_fRotatate(0)
		/*m_pTransform(new CTransformComponent)*/
	{
		m_vecComponents.resize((int)Enums::eComponentType::Size, nullptr);
		//m_vecComponents[(UINT)Enums::eComponentType::Transform] = m_pTransform;
	}

	CActor::~CActor()
	{	}
	

	void CActor::Initialize()
	{	}

	/// <summary>
	/// 배치후 호출
	/// </summary>
	void CActor::BeginPlay()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->BeginPlay();
			}
		}
		for (CComponent* pCom : m_vecCustomComponents)
		{
			pCom->BeginPlay();
		}
	}

	bool CActor::Tick()
	{
		m_vecPrevPosition = m_vecPosition;
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->TickComponent();
			}
		}

		bool state = true;
		for (CComponent* pCom : m_vecCustomComponents)
		{
			const bool currentComResult = pCom->TickComponent();
			if (state && currentComResult == false)
			{
				state = false;
			}
		}
		return state;
	}



	bool CActor::LastTick()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				pCom->LastTickComponent();
			}
		}

		bool state = true;

		for (CComponent* pCom : m_vecCustomComponents)
		{
			const bool currentComResult = pCom->LastTickComponent();
			if (state && currentComResult == false)
			{
				state = false;
			}
		}
		return state;
	}

	void CActor::FixedTick()
	{
		m_vecRenderPosition = GetPosition();
		const CCameraComponent* pCam = Renderer::CRenderer::GetMainCamera();
		if (pCam != nullptr)
		{
			m_vecRenderPosition = pCam->CaluatePosition(m_vecRenderPosition);
			m_bRenderResult = pCam->ScreenInCheck(m_vecRenderPosition, GetScale()); //화면 안에 있는지 결과를 반환
			return;
		}
		assert(false);
		m_bRenderResult = true;
	}

	
	bool CActor::Render(HDC hdc) const
	{
		if (GetRenderCheck() == false) //화면 안에 없으면 렌더 실행 취소
		{	return false;		}

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
		return true;
	}

	void CActor::Release()
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

	void CActor::ChangeLayer(const UINT layerType)
	{
		if (layerType != m_eLayerType)
		{
			GET_SINGLE(EVENT).ChangeLayer(this, layerType);
		}
	}

	//void CActor::AddTransform()
	//{
	//	if (m_pTransform == nullptr)
	//	{
	//		m_pTransform = AddComponent<CTransformComponent>();
	//	}
	//}
}