#pragma once
#include "CActor.h"
#include "CRenderer.h"

#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CObjectManager.h"

#include "CCameraComponent.h"
#include "CTransformComponent.h"
#include "CRigidbodyComponent.h"

namespace Framework
{
	CActor::CActor(UINT layerType) :
		m_eState(eState::Enable), m_eLayerType(layerType), m_uiID(0),
		m_bReserveDelete(false), m_bSafeToDelete(false), m_bDontDestroy(false), m_fRotatate(0)
		/*m_pTransform(new CTransformComponent)*/
	{
		m_vecComponents.resize((int)Enums::eComponentType::Size, nullptr);
		//m_vecComponents[(UINT)Enums::eComponentType::Transform] = m_pTransform;
	}

	CActor::~CActor()
	{
	}


	void CActor::Initialize()
	{
	}

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

		for (CActor* pActor : m_vecChilds)
		{
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

		for (CActor* pActor : m_vecChilds)
		{
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

		CalculatePosition();
		return state;
	}

	bool CActor::LastTick()
	{
		m_vecPrevPosition = m_vecWorldPosition;

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

		for (CActor* pActor : m_vecChilds)
		{
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

		for (CActor* pActor : m_vecChilds)
		{
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

		for (CActor* pActor : m_vecChilds)
		{
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
		GET_SINGLE(RENDER).Text(std::to_wstring(m_uiID), m_vecRenderPosition, Maths::Vector2(100 + m_vecRenderPosition.x, m_vecRenderPosition.y));
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

		for (CActor* pActor : m_vecChilds)
		{
			if (pActor != nullptr)
			{
				GET_SINGLE(EVENT).DeleteActor(pActor);
			}
		}
		m_vecComponents.clear();
		m_vecComponents.clear();
		m_vecChilds.clear();
	}

	void CActor::ChangeLayer(const UINT layerType)
	{
		if (layerType != m_eLayerType)
		{
			GET_SINGLE(EVENT).ChangeLayer(this, layerType);
		}
	}

	void CActor::AddChildActor(CActor* pActor)
	{
		if (pActor->GetParentActor() != nullptr)
		{
			assert(false);
			return;
		}
		const UINT32 actorID = pActor->GetID();
		if (GET_SINGLE(OBJECT).GetActor(actorID) == nullptr)
		{
			GET_SINGLE(OBJECT).AddActor(pActor);
		}
		m_vecChilds.push_back(pActor);
		pActor->SetParentActor(this);
	}

	void CActor::RemoveChild(CActor* pChild)
	{
		auto iter = std::find(m_vecChilds.begin(), m_vecChilds.end(), pChild);
		if (iter != m_vecChilds.end())
		{
			m_vecChilds.erase(iter);
		}
	}

	void CActor::CalculatePosition()
	{
		m_vecWorldPosition = m_vecPosition;
		if (m_pParent != nullptr)
		{
			m_vecWorldPosition += m_pParent->GetPosition();
		}
	}

	void CActor::CalculateRenderPosition()
	{
		m_vecRenderPosition = m_vecWorldPosition;
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