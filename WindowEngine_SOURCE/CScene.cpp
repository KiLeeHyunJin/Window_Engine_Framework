#include "CScene.h"
#include "Enums.h"
#include "CLayer.h"
#include "CActor.h"

//#include "CInputManager.h"
//#include "CCollisionManager.h"
//#include "CActor.h"

namespace Framework
{
	CScene::CScene()
	{
		//m_vecLayer = {};
		//m_vecLayer.resize((int)Enums::eLayerType::Size);
		//for (UINT i = 0; i < m_vecLayer.size(); i++)
		//{
		//	m_vecLayer[i] = new CLayer(i);
		//}
	}

	CScene::~CScene()
	{
		//for (size_t i = 0; i < m_vecLayer.size(); i++)
		//{
		//	delete m_vecLayer[i];
		//}
		//m_vecLayer.clear();
	}

	void CScene::SceneInitialize()
	{
		//for (CLayer* pLayer : m_vecLayer)
		//{
		//	pLayer->Initialize();
		//}
		Initialize();
	}

	void CScene::SceneRelease()
	{
		Release();
	}

	void CScene::SceneTick()
	{
		Tick();

	}

	void CScene::SceneLastTick()
	{
		LastTick();
	}

	//void CScene::SceneDestroy()
	//{
	//	//for (CLayer* pLayer : m_vecLayer)
	//	//{
	//	//	pLayer->Destroy();
	//	//}
	//}

	void CScene::SceneRender(HDC hdc)
	{
		//for (CLayer* pLayer : m_vecLayer)
		//{
		//	pLayer->Render(hdc);
		//}
		Render(hdc);

	}
	
	//const CLayer* CScene::GetLayer(UINT layer) const
	//{
	//	if (m_vecLayer.size() <= layer)
	//	{
	//		assert(1);
	//		return nullptr;
	//	}
	//	return m_vecLayer[layer];
	//}

	//void CScene::AddActor(CActor* pActor)
	//{
	//	const UINT layer = pActor->GetLayerType();
	//	m_vecLayer[layer]->AddActor(pActor);
	//}

	//bool CScene::EraseInLayer(CActor* pActor)
	//{
	//	const UINT objectLayer = pActor->GetLayerType();
	//	const bool result = m_vecLayer[objectLayer]->EraseInIndex(pActor);
	//	return result;
	//}
	//void CScene::EraseActor(CActor* pActor)
	//{
	//	const Enums::eLayerType objectLayer = pActor->GetLayerType();
	//	m_vecLayer[(UINT)objectLayer]->EraseActor(pActor);
	//}
}