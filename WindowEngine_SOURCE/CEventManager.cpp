#pragma once
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CTimeManager.h"

#include "CGameObject.h"

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

	void CEventManager::Tick()
	{
	}

	void CEventManager::LastTick()
	{
		Job(); //예약 실행
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

	void CEventManager::AddGameObject(CScene* pTargetScene, CGameObject* pObj, bool dontDestroy)
	{
		CScene* pScene = SCENE::GetCurrentScene();

		EventAddGameObject* newJob = new EventAddGameObject(pObj, pScene, dontDestroy);
		EventJob* parentJob = static_cast<EventJob*>(newJob);
		m_quequeEventJob.push(parentJob);
	}

	void CEventManager::DeleteGameObject(CGameObject* pObj)
	{
		if (pObj->GetReserveDelete()) //파괴 예정이라면
		{	return;		}
		CScene* pScene = SCENE::GetCurrentScene();

		EventDeleteGameObject* newJob = new EventDeleteGameObject(pObj);
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

	void CEventManager::ChangeLayer(CGameObject* pObj, UINT layerType)
	{
		if (pObj->GetReserveDelete()) //파괴 예정이라면
		{	return;		}

		CScene* currentScene = pObj->GetDontDestroy() ?  
			SCENE::GetDontDestoryScene() :
			SCENE::GetCurrentScene();

		EventChangeLayerGameObject* newJob = new EventChangeLayerGameObject(pObj, currentScene, layerType);
		EventJob* parentJob = static_cast<EventJob*>(newJob);
		m_quequeEventJob.push(parentJob);
	}

	void CEventManager::SetDontDestroyGameObject(CGameObject* pObj, bool state)
	{
		if (pObj->GetReserveDelete() || pObj->GetDontDestroy() == state) //파괴 예정이거나 이미 현재 상태라면
		{	return;		}

		CScene* currentScene = SCENE::GetCurrentScene(); //변경해야할 씬 저장
		EventSetDontDestoryGameObject* newJob = new EventSetDontDestoryGameObject(pObj, currentScene, state);
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

	void CEventManager::EventAddGameObject::operator() ()
	{
		pObj->SetDontDestroy(bDontDestroy);
		if (bDontDestroy)
		{
			pScene = SCENE::GetDontDestoryScene();
		}
		pScene->AddGameObject(pObj);
	}

	void CEventManager::EventDeleteGameObject::operator() ()
	{
		pObj->SetReserveDelete();
	}

	void CEventManager::EventChangeLayerGameObject::operator() ()
	{
		if (pObj->GetReserveDelete()) //파괴 예정이라면
		{	return;		}
		const bool result = pScene->EraseInLayer(pObj);
		if (result)
		{
			pObj->SetLayerType(layer);
			pScene->AddGameObject(pObj);
		}
	}

	void CEventManager::EventSetDontDestoryGameObject::operator() ()
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
		{	addIn->AddGameObject(pObj);		}
	}

}