#pragma once
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CTimeManager.h"

#include "CActor.h"

namespace Framework
{
	std::queue<CEventManager::EventJob*> CEventManager::m_quequeEventJob			= {};
	std::pair<const UINT, float>* CEventManager::m_pChangeScene						= nullptr;


	CEventManager::CEventManager()	{	}
	CEventManager::~CEventManager()	{	}

	void CEventManager::Initialize()
	{
	}

	void CEventManager::Release()
	{
		Clear();
	}

	void CEventManager::TickComponent()
	{
		Job(); //예약 실행
	}

	void CEventManager::LastTickComponent()
	{
		ChangeScene(); // 씬 전환
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
			m_pChangeScene->second -= CTimeManager::DeltaTime();

			if (m_pChangeScene->second <= 0)
			{
				const UINT scene = m_pChangeScene->first;
				delete m_pChangeScene;
				m_pChangeScene = nullptr;

				SCENE::LoadScene(scene);
			}
		}
	}

	void CEventManager::AddActor(CScene* pTargetScene, CActor* pObj, bool dontDestroy)
	{
		CScene* pScene = SCENE::GetCurrentScene();

		EventAddActor* newJob = new EventAddActor(pObj, pScene, dontDestroy);
		EventJob* parentJob = static_cast<EventJob*>(newJob);
		m_quequeEventJob.push(parentJob);
	}

	void CEventManager::DeleteActor(CActor* pObj)
	{
		if (pObj->GetReserveDelete()) //파괴 예정이라면
		{	return;		}
		CScene* pScene = SCENE::GetCurrentScene();

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

		CScene* currentScene = pObj->GetDontDestroy() ?  
			SCENE::GetDontDestoryScene() :
			SCENE::GetCurrentScene();

		EventChangeLayerActor* newJob = new EventChangeLayerActor(pObj, currentScene, layerType);
		EventJob* parentJob = static_cast<EventJob*>(newJob);
		m_quequeEventJob.push(parentJob);
	}

	void CEventManager::SetDontDestroyActor(CActor* pObj, bool state)
	{
		if (pObj->GetReserveDelete() || pObj->GetDontDestroy() == state) //파괴 예정이거나 이미 현재 상태라면
		{	return;		}

		CScene* currentScene = SCENE::GetCurrentScene(); //변경해야할 씬 저장
		EventSetDontDestoryActor* newJob = new EventSetDontDestoryActor(pObj, currentScene, state);
		EventJob* parentJob = static_cast<EventJob*>(newJob);
		m_quequeEventJob.push(parentJob);
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

	void CEventManager::EventAddActor::operator() ()
	{
		pObj->SetDontDestroy(bDontDestroy);
		if (bDontDestroy)
		{
			pScene = SCENE::GetDontDestoryScene();
		}
		pScene->AddActor(pObj);
	}

	void CEventManager::EventDeleteActor::operator() ()
	{
		const bool reserveDel = pObj->GetReserveDelete();
		if (reserveDel == false)
		{
			pObj->SetReserveDelete();
		}
	}

	void CEventManager::EventChangeLayerActor::operator() ()
	{
		if (pObj->GetReserveDelete()) //파괴 예정이라면
		{	return;		}
		const bool result = pScene->EraseInLayer(pObj); //레이어에서 제거 요청
		if (result) //제거가 성공적으로 일어났다면
		{
			pObj->SetLayerType(layer); //오브젝트에 레이어 변경
			pScene->AddActor(pObj);
		}
	}

	void CEventManager::EventSetDontDestoryActor::operator() ()
	{
		if (pObj->GetReserveDelete()) //파괴 예정이라면
		{	return;		}

		CScene* removeIn; //삭제해야할 씬
		CScene* addIn; //추가해야할 씬
		if (bChangeState) // 씬전환 파괴 불가 객체로 생성하고 싶을경우
		{
			removeIn = pCurrentScene;
			addIn = SCENE::GetDontDestoryScene();
		}
		else
		{
			removeIn = SCENE::GetDontDestoryScene();
			addIn = pCurrentScene;
		}

		pObj->SetDontDestroy(bChangeState);

		const bool result = removeIn->EraseInLayer(pObj);
		if (result)
		{	addIn->AddActor(pObj);		}
	}

}