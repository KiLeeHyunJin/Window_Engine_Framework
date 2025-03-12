#include "CEventManager.h"
#include "CSceneManager.h"
#include "CTimeManager.h"

#include "CScene.h"
#include "CGameObject.h"

namespace Framework
{
	std::queue<std::pair<CGameObject*, CScene*>> CEventManager::m_quequeAddObject	= {};
	std::queue<CGameObject*> CEventManager::m_quequeDeleteObject					= {};
	std::queue<std::pair<CGameObject*, CEventManager::LayerData>> CEventManager::m_quequeChangeLayerObject = {};
	std::pair<const UINT, float>* CEventManager::m_pChangeScene						= nullptr;

	CEventManager::CEventManager()	{	}
	CEventManager::~CEventManager()	{	}

	void CEventManager::Initialize()
	{
	}

	void CEventManager::Release()
	{
	}

	void CEventManager::Tick()
	{
		ProgressAddGameObject();
		ProgressDeleteGameObject();

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

	void CEventManager::LastTick()
	{
		ProgressChangeLayer();
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

	void CEventManager::ChangeLayer(CGameObject* pObj, Enums::eLayerType layerType)
	{
		CScene* currentScene = SCENE::GetCurrentScene();
		m_quequeChangeLayerObject.push(std::pair(pObj, LayerData(currentScene, layerType)));
	}

	void CEventManager::SetDontDestroyGameObject(CGameObject* pObj)
	{
		CScene* currentScene = SCENE::GetCurrentScene();
		const bool result = currentScene->EraseInLayer(pObj);
		if (result)
		{
			SCENE::GetDontDestoryScene()->AddGameObject(pObj);
		}
	}

	void CEventManager::ProgressAddGameObject()
	{
		while (m_quequeAddObject.empty() == false)
		{
			const std::pair<CGameObject*, CScene*> pair = m_quequeAddObject.front();
			m_quequeAddObject.pop();

			CGameObject* pObj = pair.first;
			CScene* currentScene = pObj->GetDontDestroy() ?
				SCENE::GetDontDestoryScene() : 
				pair.second;

			currentScene->AddGameObject(pObj);
		}
	}

	void CEventManager::ProgressDeleteGameObject()
	{
		while (m_quequeDeleteObject.empty() == false)
		{
			CGameObject* obj = m_quequeDeleteObject.front();
			m_quequeDeleteObject.pop();
			obj->SetReserveDelete();
		}
	}

	void CEventManager::ProgressChangeLayer()
	{
		while (m_quequeChangeLayerObject.empty() == false)
		{
			std::pair<CGameObject*, CEventManager::LayerData> layerData = m_quequeChangeLayerObject.front();
			m_quequeChangeLayerObject.pop();

			CGameObject* pObj = layerData.first;
			CScene* pScene = layerData.second.scene;
			Enums::eLayerType eLayer = layerData.second.targetLayer;

			const bool result = pScene->EraseInLayer(pObj);
			if (result)
			{
				pObj->SetLayerType(eLayer);
				pScene->AddGameObject(pObj);
			}
		}
	}


	void CEventManager::AddGameObject(CScene* pTargetScene, CGameObject* pObj, bool dontDestroy)
	{
		pObj->SetDontDestroy(dontDestroy);
		m_quequeAddObject.push(std::pair(pObj, pTargetScene));
	}

	void CEventManager::Clear()
	{
		while (m_quequeDeleteObject.empty() == false)
		{
			m_quequeDeleteObject.pop();
		}
		while (m_quequeAddObject.empty() == false)
		{
			m_quequeAddObject.pop();
		}
	}

}