#pragma once
#include "CActor.h"
#include "CRenderer.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CObjectManager.h"

#include "CCameraComponent.h"
//#include "CRigidbodyComponent.h"

namespace Framework
{
	CActor::CActor(UINT layerType) :
		m_eState(eState::Enable), m_eLayerType(layerType), m_uiID(0), m_fRotatate(0)
	{
		m_vecComponents.resize((int)Enums::eComponentType::Size, nullptr);
	}

	CActor::~CActor()
	{
	}


	void CActor::Initialize()
	{
	}

	/// <summary>
	/// 필드 배치후 호출
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

		for (UINT actorID : m_vecChilds)
		{
			CActor* pActor = GET_SINGLE(OBJECT).GetActor(actorID);
			if (pActor->GetDisable())
			{
				continue;
			}
			pActor->BeginPlay();
		}
	}

	bool CActor::Tick()
	{
		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				if (pCom->GetDisable())
				{
					continue;
				}

				pCom->TickComponent();
			}
		}

		bool state = true;
		for (CComponent* pCom : m_vecCustomComponents)
		{
			if (pCom->GetDisable())
			{
				continue;
			}

			const bool currentComResult = pCom->TickComponent();
			if (state && currentComResult == false)
			{
				state = false;
			}
		}

		for (UINT actorID : m_vecChilds)
		{
			CActor* pActor = GET_SINGLE(OBJECT).GetActor(actorID);
			if (pActor->GetDisable())
			{
				continue;
			}
			if (pActor->GetReserveDelete() == false)
			{
				if (pActor->Tick() == false)
				{
					pActor->SetReserveDelete();
				}
			}
		}

		return state;
	}

	bool CActor::LastTick()
	{
		CalculatePosition();

		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				if (pCom->GetDisable())
				{
					continue;
				}

				pCom->LastTickComponent();
			}
		}

		bool state = true;

		for (CComponent* pCom : m_vecCustomComponents)
		{
			if (pCom->GetDisable())
			{
				continue;
			}

			const bool currentComResult = pCom->LastTickComponent();
			if (state && currentComResult == false)
			{
				state = false;
			}
		}

		for (UINT actorID : m_vecChilds)
		{
			CActor* pActor = GET_SINGLE(OBJECT).GetActor(actorID);
			if (pActor->GetDisable())
			{
				continue;
			}
			if (pActor->GetReserveDelete() == false)
			{
				if (pActor->LastTick() == false)
				{
					pActor->SetReserveDelete();
				}
			}
		}

		return state;
	}

	void CActor::FixedTick()
	{
		m_vecPrevWorldPosition = m_vecCurWorldPosition;
		//CalculatePosition();

		for (CComponent* pCom : m_vecComponents)
		{
			if (pCom != nullptr)
			{
				if (pCom->GetDisable())
				{
					continue;
				}

				pCom->FixedComponent();
			}
		}

		bool state = true;

		for (CComponent* pCom : m_vecCustomComponents)
		{
			if (pCom->GetDisable())
			{
				continue;
			}

			pCom->FixedComponent();
		}

		for (UINT actorID : m_vecChilds)
		{
			CActor* pActor = GET_SINGLE(OBJECT).GetActor(actorID);
			if (pActor->GetDisable())
			{
				continue;
			}
			if (pActor->GetReserveDelete() == false)
			{
				pActor->FixedTick();
			}
		}

		CalculateRenderPosition();
	}


	bool CActor::Render(HDC hdc) const
	{
		if (GetRenderCheck() == false) //화면 안에 없으면 렌더 실행 취소
		{
			return false;
		}

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

		for (UINT actorID : m_vecChilds)
		{
			CActor* pActor = GET_SINGLE(OBJECT).GetActor(actorID);
			if (pActor->GetDisable())
			{
				continue;
			}
			if (pActor->GetReserveDelete() == false)
			{
				pActor->Render(hdc);
			}
		}



		GET_SINGLE(RENDER).FrameCircle(m_vecRenderPosition, 2.f);
		GET_SINGLE(RENDER).Text(std::to_wstring(m_uiID), 
			m_vecRenderPosition, 
			Maths::Vector2(100 + m_vecRenderPosition.x, m_vecRenderPosition.y));
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

		for (UINT actorID : m_vecChilds)
		{
			CActor* pActor = GET_SINGLE(OBJECT).GetActor(actorID);
			if (pActor != nullptr)
			{
				pActor->Release();
			}
		}

		m_vecComponents.clear();
		m_vecComponents.clear();
		m_vecChilds.clear();
		//GET_SINGLE(OBJECT).RemoveActor(GetID());
	}

	void CActor::ChangeLayer(const UINT layerType)
	{
		if (layerType != m_eLayerType)
		{
			GET_SINGLE(EVENT).ChangeLayer(this, layerType);
		}
	}

	void CActor::AddChildID(UINT actorID)
	{
		if (GET_SINGLE(OBJECT).GetActor(actorID)->GetParentID() != 0)
		{
			assert(false);
			return;
		}
		CActor* pActor = GET_SINGLE(OBJECT).GetActor(actorID);
		if (pActor != nullptr)
		{
			m_vecChilds.push_back(actorID);
			pActor->SetParentID(GetID());
			return;
		}
		assert(false);
	}

	void CActor::RemoveChild(UINT childID)
	{
		auto iter = std::find(m_vecChilds.begin(), m_vecChilds.end(), childID);
		if (iter != m_vecChilds.end())
		{
			m_vecChilds.erase(iter);
		}
	}

	void CActor::CalculatePosition()
	{
		m_vecCurWorldPosition = m_vecLocalPosition;
		if (m_uiParentID != 0)
		{
			const CActor* parent = GET_SINGLE(OBJECT).GetActor(m_uiParentID);
			if (parent != nullptr)
			{
				m_vecCurWorldPosition += parent->GetPosition();
			}
		}
	}

	void CActor::CalculateRenderPosition()
	{
		m_vecRenderPosition = m_vecCurWorldPosition;
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

}