#pragma once
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CTimeManager.h"

#include "CGameObject.h"

namespace Framework
{
	std::queue<std::pair<CGameObject*, CEventManager::LayerData>> CEventManager::m_quequeObject	= {};
	std::queue<std::pair<CGameObject*, CEventManager::LayerData>> CEventManager::m_quequeChange = {};
	//std::queue<CGameObject*> CEventManager::m_quequeDeleteObject					= {};
	std::pair<const UINT, float>* CEventManager::m_pChangeScene						= nullptr;
	CEventManager::EventFuncPtr CEventManager::ProgressFunc[static_cast<int>(CEventManager::eEventType::Size)] = {};

	CEventManager::CEventManager()	{	}
	CEventManager::~CEventManager()	{	}

	void CEventManager::Initialize()
	{
		ProgressFunc[(INT)eEventType::Delete]	= &ProgressDeleteGameObject;
		ProgressFunc[(INT)eEventType::Add]		= &ProgressAddGameObject;
		ProgressFunc[(INT)eEventType::Layer]	= &ProgressChangeLayer;
		ProgressFunc[(INT)eEventType::Scene]	= &ProgressDontDestroy;

	}

	void CEventManager::Release()
	{
	}

	void CEventManager::Tick()
	{
		ProgressLifeObject(); //게임 오브젝트 추가 삭제
	}

	void CEventManager::LastTick()
	{
		ProgressChangeObject(); // 게임 오브젝트 레이어, 씬 변경
		ProgressChangeScene(); // 씬 전환
	}

	void CEventManager::ProgressLifeObject()
	{
		while (m_quequeObject.empty() == false)
		{
			std::pair<CGameObject*, LayerData> pair = m_quequeObject.front();
			m_quequeObject.pop();
			
			CGameObject* pObj = pair.first;
			ProgressFunc[(INT)pair.second.eEventType](pObj, pair.second);
		}
	}

	void CEventManager::ProgressChangeObject()
	{
		while (m_quequeChange.empty() == false)
		{
			std::pair<CGameObject*, LayerData> pair = m_quequeChange.front();
			m_quequeChange.pop();

			CGameObject* pObj = pair.first;
			ProgressFunc[(INT)pair.second.eEventType](pObj, pair.second);
		}
	}

	void CEventManager::ProgressAddGameObject(CGameObject* pObj, LayerData& data)
	{
		CScene* currentScene = pObj->GetDontDestroy() ?
			SCENE::GetDontDestoryScene() :
			data.pScene;

		currentScene->AddGameObject(pObj);
	}

	void CEventManager::ProgressDeleteGameObject(CGameObject* pObj, LayerData& data)
	{
		pObj->SetReserveDelete();
	}

	void CEventManager::ProgressChangeLayer(CGameObject* pObj, LayerData& data)
	{
		const bool result = data.pScene->EraseInLayer(pObj);
		if (result)
		{
			Enums::eLayerType eLayer = data.eTargetLayer;

			pObj->SetLayerType(eLayer);
			data.pScene->AddGameObject(pObj);
		}
	}

	void CEventManager::ProgressDontDestroy(CGameObject* pObj, LayerData& data)
	{
		const bool result = data.pScene->EraseInLayer(pObj);
		if (result)
		{
			SCENE::GetDontDestoryScene()->AddGameObject(pObj);
		}
	}

	void CEventManager::ProgressChangeScene()
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
		pObj->SetDontDestroy(dontDestroy);
		m_quequeObject.push(
			std::pair(pObj, LayerData(eEventType::Add, pTargetScene)));
	}

	void CEventManager::DeleteGameObject(CGameObject* pObj)
	{
		CScene* pScene = SCENE::GetCurrentScene();
		m_quequeObject.push(
			std::pair(pObj, LayerData(eEventType::Delete, pScene)));
	}


	/// <summary>
	/// LastTick에서 처리
	/// </summary>
	/// <param name="loadSceneID">Enum값으로 지정하는것을 추천</param>
	/// <param name="changeTime">전환 예약 시간</param>
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

	/// <summary>
	/// LastTick에서 처리
	/// </summary>
	/// <param name="pObj"></param>
	/// <param name="layerType"></param>
	void CEventManager::ChangeLayer(CGameObject* pObj, Enums::eLayerType layerType)
	{
		CScene* currentScene = pObj->GetDontDestroy() ?  
			SCENE::GetDontDestoryScene() :
			SCENE::GetCurrentScene();

		m_quequeChange.push(
			std::pair(pObj, LayerData(eEventType::Layer, currentScene, layerType)));
	}

	void CEventManager::SetDontDestroyGameObject(CGameObject* pObj)
	{
		if (pObj->GetDontDestroy())
		{	return;		}

		CScene* currentScene = SCENE::GetCurrentScene();
		m_quequeChange.push(
			std::pair(pObj, LayerData(eEventType::Scene, currentScene)));


	}



	void CEventManager::Clear()
	{
		while (m_quequeObject.empty() == false)
		{
			m_quequeObject.pop();
		}
		while (m_quequeChange.empty() == false)
		{
			m_quequeChange.pop();
		}
	}

}