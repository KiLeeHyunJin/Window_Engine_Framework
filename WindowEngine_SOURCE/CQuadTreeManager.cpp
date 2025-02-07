#include "CQuadTreeManager.h"
#include "CQuadTree.h"

namespace Framework
{
    CQuadTree* CQuadTreeManager::m_pQuadTree = nullptr;

    CQuadTreeManager::CQuadTreeManager()
    {
    }

    CQuadTreeManager::~CQuadTreeManager()
    {
    }

    void CQuadTreeManager::Initialize(Maths::Vector2 size, int maxDepth, float constrantK)
    {
        if (m_pQuadTree != nullptr)
        {
            m_pQuadTree->Release();
            m_pQuadTree = nullptr;
        }
        m_pQuadTree = new CQuadTree(size, maxDepth, constrantK);
    }
    std::list<CColliderComponent*> CQuadTreeManager::Query(CColliderComponent* queryItem)
    {
        return m_pQuadTree->Query(queryItem);
    }

    void CQuadTreeManager::Clear()
    {
        m_pQuadTree->Clear();
    }

    void CQuadTreeManager::Release()
    {
        m_pQuadTree->Release();
        delete m_pQuadTree;
    }

    void CQuadTreeManager::Insert(CColliderComponent* pCollider)
    {
        m_pQuadTree->Insert(pCollider);
    }


}