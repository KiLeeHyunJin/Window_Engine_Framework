#include "CCollisionManager.h"
#include "CSceneManager.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CTransformComponent.h"
#include "CColliderComponent.h"
#include "CQuadTreeManager.h"
//#include 

namespace Framework
{
	std::bitset<(UINT)Enums::eLayerType::Size> CCollisionManager::m_bsCollisionCheck[(UINT)Enums::eLayerType::Size] = {false};
	std::unordered_map<UINT64, bool> CCollisionManager::m_unmapCollisions = {};

	CCollisionManager::CCollisionManager()
	{	}
	CCollisionManager::~CCollisionManager()
	{	}

	void CCollisionManager::SetCollisionLayerState(Enums::eLayerType left, Enums::eLayerType right, bool enable)
	{
		UINT row;
		UINT col;
		if (left <=  right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			col = (UINT)left;
			row = (UINT)right;
		}
		m_bsCollisionCheck[row][col] = enable;
	}

	const std::list<CColliderComponent*>& CCollisionManager::GetCollisionCollider(const Maths::Vector2& center, const Maths::Vector2& size)
	{
		return CQuadTreeManager::Query(center, size);
	}

	const std::list<CColliderComponent*>& CCollisionManager::GetCollisionCollider(const Rect& rect)
	{
		Maths::Vector2 center = (rect.max + rect.min) * 0.5f;
		Maths::Vector2 size = rect.max - rect.min;

		return GetCollisionCollider(center, size);
	}


	void CCollisionManager::Initialize()
	{
		CQuadTreeManager::Initialize(Maths::Vector2(1024, 1024), 6, 2);
	}

	void CCollisionManager::Release()
	{
		CQuadTreeManager::Release();
	}

	void CCollisionManager::Tick()
	{
		CQuadTreeManager::Clear();

		CScene* pScene = CSceneManager::GetCurrentScene();
		if (pScene == nullptr)				{	return;	}

		if(true) //쿼드트리
		{
			std::list<CColliderComponent*> listCollider;
			InsertCollision(listCollider);
			CollisionCircuit(listCollider);
		}
		else //브루트포스
		{
			for (UINT row = 0; row < (UINT)Enums::eLayerType::Size; row++)
			{
				for (UINT col = 0; col < (UINT)Enums::eLayerType::Size; col++)
				{
					if (m_bsCollisionCheck[row][col])
					{
						CollisionCheck(pScene, (Enums::eLayerType)row, (Enums::eLayerType)col);
					}
				}
			}
		}
	}

	void CCollisionManager::LastTick()
	{	}

	void CCollisionManager::Render(HDC hdc)
	{
		CQuadTreeManager::Render(hdc);
	}

	void CCollisionManager::CollisionCheck(CScene* pScene, Enums::eLayerType left, Enums::eLayerType right)
	{
		const std::vector<CGameObject*>& lefts = CSceneManager::GetGameObject(left);
		const std::vector<CGameObject*>& rights = CSceneManager::GetGameObject(right);

		for (CGameObject* leftObj : lefts)
		{

			if (leftObj == nullptr)
			{
				continue;
			}
			if (leftObj->GetActive() == false)
			{
				continue;
			}
			CColliderComponent* leftCollider = leftObj->GetComponent<CColliderComponent>();
			if (leftCollider == nullptr)
			{
				continue;
			}

			for (CGameObject* rightObj : rights)
			{
				if (leftObj == rightObj)
				{
					continue;
				}
				if (rightObj == nullptr)
				{
					continue;
				}
				if (rightObj->GetActive() == false)
				{
					continue;
				}
				CColliderComponent* rightCollider = rightObj->GetComponent<CColliderComponent>();
				if (rightCollider == nullptr)
				{
					continue;
				}
				CollisionStateUpdate(leftCollider, rightCollider);
			}
		}
	}



	void CCollisionManager::CollisionStateUpdate(CColliderComponent* leftCollider, CColliderComponent* rightCollider)
	{
		CollisionID collId = { leftCollider->GetID() , rightCollider->GetID()};

		auto iter = m_unmapCollisions.find(collId.id);
		
		if (iter == m_unmapCollisions.end())
		{
			m_unmapCollisions.insert(std::make_pair(collId.id, false));
			iter = m_unmapCollisions.find(collId.id);
		}

		if (Intersect(leftCollider, rightCollider))
		{
			if (iter->second == false) //첫 충돌
			{
				leftCollider->OnCollisionEnter(rightCollider);
				rightCollider->OnCollisionEnter(leftCollider);
				iter->second = true;
			}
			else // 충돌 중
			{
				leftCollider->OnCollisionStay(rightCollider);
				rightCollider->OnCollisionStay(leftCollider);
			}
		}
		else
		{
			if (iter->second == true) //충돌 해제
			{
				leftCollider->OnCollisionExit(rightCollider);
				rightCollider->OnCollisionExit(leftCollider);
				iter->second = false;
			}
		}

	}

	void CCollisionManager::Clear()
	{
		CQuadTreeManager::Clear();
		m_unmapCollisions.clear();
		m_bsCollisionCheck->reset();
	}

	bool CCollisionManager::Raycast(const Ray& ray, CColliderComponent& hitObject)
	{
		return CQuadTreeManager::Raycast(ray, hitObject);
	}

	const bool CCollisionManager::Intersect(const CColliderComponent* left, const CColliderComponent* right)
	{
		const CColliderComponent::eColliderType leftType = left->GetColliderType();
		const CColliderComponent::eColliderType rightType = right->GetColliderType();

		if (leftType == CColliderComponent::eColliderType::Box &&
			rightType == CColliderComponent::eColliderType::Box)
		{
			return BoxCollisionStateUpdate(left, right);
		}
		else if (leftType == CColliderComponent::eColliderType::Circle &&
			rightType == CColliderComponent::eColliderType::Circle)
		{
			return CircleCollisionStateUpdate(left, right);
		}
		return false;
	}

	void CCollisionManager::InsertCollision(std::list<CColliderComponent*>& listCollider)
	{
		for (UINT layer = 0; layer < (UINT)Enums::eLayerType::Size; layer++)
		{
			const std::vector<CGameObject*>& listObj = CSceneManager::GetGameObject((Enums::eLayerType)layer);
			for (const auto& pGameObject : listObj)
			{
				if (pGameObject->GetActive())
				{
					CColliderComponent* pCollider = pGameObject->GetComponent<CColliderComponent>();
					if (pCollider != nullptr)
					{
						CQuadTreeManager::Insert(pCollider);
						listCollider.push_back(pCollider);
					}
				}
			}
		}
	}

	void CCollisionManager::CollisionCircuit(const std::list<CColliderComponent*>& listCollider)
	{
		for (const auto& pCollider : listCollider)
		{
			const UINT leftLayer = (UINT)pCollider->GetOwner()->GetLayerType();

			const std::list<CColliderComponent*>& possibleList = CQuadTreeManager::Query(pCollider);
			for (const auto& possibleColl : possibleList)
			{
				if (pCollider != possibleColl)
				{
					const UINT rightLayer = (UINT)possibleColl->GetOwner()->GetLayerType();
					if (m_bsCollisionCheck[leftLayer][rightLayer])
					{
						CollisionStateUpdate(pCollider, possibleColl);
					}
				}
			}
		}
	}


	bool CCollisionManager::BoxCollisionStateUpdate(const CColliderComponent* left,const CColliderComponent* right)
	{
		const CTransformComponent* leftTr = left->GetOwner()->GetTransformComponent();
		const CTransformComponent* rightTr = right->GetOwner()->GetTransformComponent();

		const Maths::Vector2 leftPos = leftTr->GetPos() + left->GetOffset();
		const Maths::Vector2 rightPos = rightTr->GetPos() + right->GetOffset();

		const Maths::Vector2 leftSize = left->GetSize();
		const Maths::Vector2 rightSize = right->GetSize();

		if (Maths::Abs(leftPos.x - rightPos.x) < Maths::Abs((leftSize.x + rightSize.x) * 0.5f) &&
			Maths::Abs(leftPos.y - rightPos.y) < Maths::Abs((leftSize.y + rightSize.y) * 0.5f))
		{
			return true;
		}
		return false;
	}

	bool CCollisionManager::CircleCollisionStateUpdate(const CColliderComponent* left, const CColliderComponent* right)
	{
		const CTransformComponent* leftTr = left->GetOwner()->GetComponent<CTransformComponent>();
		const CTransformComponent* rightTr = right->GetOwner()->GetComponent<CTransformComponent>();

		Maths::Vector2 leftPos = leftTr->GetPos() + left->GetOffset();
		Maths::Vector2 rightPos = rightTr->GetPos() + right->GetOffset();

		Maths::Vector2 leftSize = left->GetSize() * 100;
		Maths::Vector2 rightSize = right->GetSize() * 100;

		const Maths::Vector2 leftCirclePos	= leftPos  + (leftSize * 0.5f);
		const Maths::Vector2 rightCirclePos = rightPos + (rightSize * 0.5f);

		const float lenght = (Maths::Vector2(leftCirclePos.x + rightCirclePos.x, leftCirclePos.y + rightCirclePos.y)).Length();

		if (lenght <= (leftSize.x + rightSize.x) * 0.5f)
		{
			return true;
		}
		return false;
	}




}
