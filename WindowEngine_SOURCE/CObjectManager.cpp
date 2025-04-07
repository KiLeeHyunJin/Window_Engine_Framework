#include "CObjectManager.h"
#include "CActor.h"
#include "CCollisionManager.h"
namespace Framework
{

	UINT CObjectManager::m_uiLayerSize									= 0;
	std::unordered_map<UINT32, CActor*> CObjectManager::m_unObjects		= {};

	std::vector<CLayer*> CObjectManager::m_vecLayer						= {};
	std::vector<CLayer*> CObjectManager::m_vecDontDestoryLayer			= {};

	CObjectManager::~CObjectManager()
	{
	}

	void CObjectManager::AddActor(CActor* pActor)
	{
		const UINT layer = pActor->GetLayerType();
		const UINT32 id = pActor->GetID();
		m_vecLayer[layer]->AddActor(pActor);
		m_unObjects.insert(std::make_pair(id, pActor));
	}

	bool CObjectManager::EraseInLayer(CActor* pActor)
	{
		const UINT objectLayer = pActor->GetLayerType();
		const bool result = m_vecLayer[objectLayer]->EraseInIndex(pActor);
		return result;
	}

	void CObjectManager::InitLayerSize(UINT layerSize)
	{
		if (m_uiLayerSize != 0)	//데이터가 설정되었을 경우 변경 불가
		{
			return;
		}
		m_uiLayerSize = layerSize;

		m_vecDontDestoryLayer.resize(m_uiLayerSize);
		m_vecLayer.resize(m_uiLayerSize);

		COLLISION::InitCollisionLayer();
	}

	void CObjectManager::Initialize()
	{
	}

	void CObjectManager::Release()
	{
	}
	void CObjectManager::TickComponent()
	{
	}
	void CObjectManager::LastTickComponent()
	{
	}
	void CObjectManager::Render(HDC hdc)
	{
	}
}
