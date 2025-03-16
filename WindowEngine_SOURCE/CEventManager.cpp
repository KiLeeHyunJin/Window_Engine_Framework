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
		Job(); //���� ����
		ChangeScene(); // �� ��ȯ
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
		if (pObj->GetReserveDelete()) //�ı� �����̶��
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
		if (pObj->GetReserveDelete()) //�ı� �����̶��
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
		if (pObj->GetReserveDelete() || pObj->GetDontDestroy() == state) //�ı� �����̰ų� �̹� ���� ���¶��
		{	return;		}

		CScene* currentScene = SCENE::GetCurrentScene(); //�����ؾ��� �� ����
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
		if (pObj->GetReserveDelete()) //�ı� �����̶��
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
		if (pObj->GetReserveDelete()) //�ı� �����̶��
		{	return;		}

		CScene* removeIn; //�����ؾ��� ��
		CScene* addIn; //�߰��ؾ��� ��
		if (bChangeState) // ����ȯ �ı� �Ұ� ��ü�� �����ϰ� �������
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