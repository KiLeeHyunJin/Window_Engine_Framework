#include "CQuadTreeManager.h"
#include "CQuadTree.h"
#include <limits.h>

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
    const std::vector<CColliderComponent*>& CQuadTreeManager::Query(CColliderComponent* queryItem)
    {
        return m_pQuadTree->Query(queryItem);
    }

    const std::vector<CColliderComponent*>& CQuadTreeManager::Query(const Maths::Vector2& center, const Maths::Vector2& size)
    {
        return m_pQuadTree->Query(center, size);
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

    void CQuadTreeManager::Render(HDC hdc)
    {
        m_pQuadTree->Render(hdc);
    }


    void CQuadTreeManager::Insert(CColliderComponent* pCollider)
    {
        m_pQuadTree->Insert(pCollider);
    }

    bool CQuadTreeManager::Raycast(const Ray& ray, CColliderComponent& hitObject, const std::vector<CColliderComponent*>& ignores)
    {
        float closestHit = FLT_MAX;
        return m_pQuadTree->Raycast(ray, closestHit, hitObject, ignores);
    }

    bool CQuadTreeManager::Raycast(const Ray& ray, CColliderComponent& hitObject, const std::vector<Enums::eLayerType>& checkLayers)
    {
        float closestHit = FLT_MAX;
        return m_pQuadTree->Raycast(ray, closestHit, hitObject, checkLayers);
    }

}