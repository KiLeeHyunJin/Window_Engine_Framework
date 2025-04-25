#pragma once
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CTimeManager.h"
#include "CObjectManager.h"

#include "CActor.h"

namespace Framework
{

	namespace Manager
	{
		CEventManager* CEventManager::s_instance = nullptr;

		//std::queue<CEventManager::EventJob*> CEventManager::m_quequeEventJob = {};
		//std::pair<const UINT, float>* CEventManager::m_pChangeScene = nullptr;


		//CEventManager::CEventManager() {}
		CEventManager::~CEventManager() {}

		void CEventManager::Initialize()
		{
		}

		void CEventManager::Release()
		{
			Clear();
		}

		void CEventManager::Tick()
		{
			Job(); //예약 실행
		}

		void CEventManager::LastTick()
		{
			ChangeScene(); // 씬 전환
		}

		void CEventManager::Clear()
		{
			while (m_quequeEventJob.empty() == false)
			{
				EventJob* pJob = m_quequeEventJob.front();
				m_quequeEventJob.pop();
				delete pJob;
			}

			if (m_pChangeScene != nullptr)
			{
				delete m_pChangeScene;
			}
			m_pChangeScene = nullptr;
		}

		void CEventManager::Job()
		{
			while (m_quequeEventJob.empty() == false)
			{
				EventJob* job = m_quequeEventJob.front();
				m_quequeEventJob.pop();
				(*job)();
				delete job;
			}
		}

		void CEventManager::ChangeScene()
		{
			if (nullptr != m_pChangeScene)
			{
				float& waitTime = m_pChangeScene->second;
				waitTime -= GET_SINGLE(TIME).DeltaTime();

				if (waitTime <= 0)
				{
					const UINT scene = m_pChangeScene->first;
					SAFE_DELETE(m_pChangeScene);

					GET_SINGLE(SCENE).LoadScene(scene);
				}
			}
		}

		void CEventManager::AddActor(CActor* pObj, bool dontDestroy)
		{
			EventAddActor* newJob = new EventAddActor(pObj, dontDestroy);
			//pObj->SetLayerType(layerType);
			EventJob* parentJob = static_cast<EventJob*>(newJob);
			m_quequeEventJob.push(parentJob);
		}

		void CEventManager::DeleteActor(CActor* pObj)
		{
			if (pObj->GetReserveDelete()) //파괴 예정이라면
			{	return;		}

			EventDeleteActor* newJob = new EventDeleteActor(pObj);
			EventJob* parentJob = static_cast<EventJob*>(newJob);
			m_quequeEventJob.push(parentJob);
		}


		void CEventManager::LoadScene(UINT loadSceneID, float changeTime)
		{
			if (m_pChangeScene == nullptr)
			{
				m_pChangeScene = new std::pair<const UINT, float>(loadSceneID, changeTime);
			}
			else if (m_pChangeScene->second > changeTime)
			{
				delete m_pChangeScene;
				m_pChangeScene = new std::pair<const UINT, float>(loadSceneID, changeTime);
			}
		}

		void CEventManager::ChangeLayer(CActor* pObj, UINT layerType)
		{
			if (pObj->GetReserveDelete()) //파괴 예정이라면
			{	return;		}

			EventChangeLayerActor* newJob = new EventChangeLayerActor(pObj, layerType);
			EventJob* parentJob = static_cast<EventJob*>(newJob);
			m_quequeEventJob.push(parentJob);
		}

		void CEventManager::SetDontDestroyActor(CActor* pObj, bool state)
		{
			if (pObj->GetReserveDelete() || pObj->GetDontDestroy() == state) //파괴 예정이거나 이미 현재 상태라면
			{	return;		}

			EventSetDontDestoryActor* newJob = new EventSetDontDestoryActor(pObj, state);
			EventJob* parentJob = static_cast<EventJob*>(newJob);
			m_quequeEventJob.push(parentJob);
		}





		/// <summary>
		/// EventJob
		/// </summary>

		void CEventManager::EventAddActor::operator() ()
		{
			pObj->SetDontDestroy(bDontDestroy);
			GET_SINGLE(OBJECT).AddActor(pObj);
		}

		void CEventManager::EventDeleteActor::operator() ()
		{
			const bool reserveDel = pObj->GetReserveDelete();
			if (reserveDel == false)
			{
				pObj->SetReserveDelete();
				GET_SINGLE(OBJECT).RemoveActor(pObj->GetID());
			}
		}

		void CEventManager::EventChangeLayerActor::operator() ()
		{
			if (pObj->GetReserveDelete()) //파괴 예정이라면
			{	return;		}
			const bool result = GET_SINGLE(OBJECT).EraseInLayer(pObj);//pScene->EraseInLayer(pObj); //레이어에서 제거 요청
			if (result) //제거가 성공적으로 일어났다면
			{
				pObj->SetLayerType(layer); //오브젝트에 레이어 변경
				GET_SINGLE(OBJECT).AddInLayer(pObj);
			}
		}

		void CEventManager::EventSetDontDestoryActor::operator() ()
		{
			if (pObj->GetReserveDelete()) //파괴 예정이라면
			{	return;		}
			pObj->SetDontDestroy(bChangeState);
			GET_SINGLE(OBJECT).AddActor(pObj);
		}
	}

	

}