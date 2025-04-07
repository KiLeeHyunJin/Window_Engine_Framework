#include "CSceneManager.h"
#include "CDontDestroyOnLoad.h"

#include "CRenderManager.h"
#include "CCollisionManager.h"
#include "CUIManager.h"
#include "Utils.h"

namespace Framework
{
	std::vector<CScene*>	CSceneManager::m_vecScenes				= {nullptr};
	CScene* CSceneManager::m_pCurrentScene							= nullptr;
	CScene*	CSceneManager::m_pDontDestroyScene						= nullptr;
	UINT	CSceneManager::m_uiLayerSize = 0;

	CSceneManager::CSceneManager()
	{
	}

	CSceneManager::~CSceneManager()
	{
	}

	void CSceneManager::Initialize()
	{
		InitDontDestroyScene();
	}

	void CSceneManager::TickComponent()
	{
		m_pCurrentScene->SceneTickComponent();
		m_pDontDestroyScene->SceneTickComponent();

	}

	void CSceneManager::LastTickComponent()
	{
		m_pCurrentScene->SceneLastTickComponent();
		m_pDontDestroyScene->SceneLastTickComponent();
	}

	void CSceneManager::Destroy()
	{
		m_pCurrentScene->SceneDestroy();
		m_pDontDestroyScene->SceneDestroy();
	}

	void CSceneManager::Render(HDC hDC)
	{
		m_pCurrentScene->Render(hDC);

		for (UINT i = (UINT)Enums::eLayerType::None; i < (UINT)Enums::eLayerType::Size; i++)
		{
			const CLayer* pCurrentLayer = m_pCurrentScene->GetLayer(i);
			const CLayer* pDontDestroyLayer = m_pDontDestroyScene->GetLayer(i);

			pCurrentLayer->Render(hDC);
			pDontDestroyLayer->Render(hDC);
		}

		m_pCurrentScene->LastRender(hDC);
		
		std::wstring str = m_pCurrentScene->GetName();
		Utils::DrawTxt(hDC, Maths::Vector2(0, 15), str);
	}

	void CSceneManager::Release()
	{
		for (auto& pScene : m_vecScenes)
		{
			if (pScene != nullptr)
			{
				pScene->OnExit();
				pScene->SceneRelease();
				delete pScene;
			}
		}
		m_vecScenes.clear();

		m_pCurrentScene = nullptr;
		m_pDontDestroyScene = nullptr;
	}

	//const std::vector<CActor*>& CSceneManager::GetDontDestroyActor(UINT layer)
	//{
	//	return m_pDontDestroyScene->GetLayer(layer)->GetActor();
	//}

	//const std::vector<CActor*>& CSceneManager::GetActor(UINT layer)
	//{
	//	return  m_pCurrentScene->GetLayer(layer)->GetActor();
	//}

	CScene* CSceneManager::LoadScene(const UINT idx)
	{
		CScene* pScene = FindScene(idx);
		if (pScene != nullptr)
		{
			if (m_pCurrentScene != nullptr)
			{
				m_pCurrentScene->OnExit();
				CCollisionManager::Clear();
				CUIManager::Clear();
			}

			m_pCurrentScene = pScene;
			m_pCurrentScene->OnEnter();
			return m_pCurrentScene;
		}
		return nullptr;
	}

	CScene* CSceneManager::FindScene(const UINT idx)
	{
		if (m_vecScenes.size() <= idx)
		{
			assert(true);
		}
		CScene* pScene = m_vecScenes[idx];
		//std::map<std::wstring, CScene*>::iterator iter = m_mapScene.find(name);
		/*if (iter != m_mapScene.end())
		{
			return iter->second;
		}*/
		return pScene;
	}

	void CSceneManager::InitDontDestroyScene()
	{
		CDontDestroyOnLoad* pDontDestroyScene = new CDontDestroyOnLoad;
		m_pDontDestroyScene = static_cast<CScene*>(pDontDestroyScene);
		m_pDontDestroyScene->SetName(L"DontDestroyScene");
		m_pDontDestroyScene->SceneInitialize();
	}

	void CSceneManager::InitSceneSize(UINT size)
	{
		if (m_vecScenes.size() >= size)	
		{
			return;
		}

		if (m_vecScenes.size() < size)
		{
			m_vecScenes.resize(size);
			m_vecScenes[m_vecScenes.size() - 1] = m_pDontDestroyScene;
		}
		//COLLISION::InitCollisionLayer();
	}
}