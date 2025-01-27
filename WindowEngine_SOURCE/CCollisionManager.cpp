#include "CCollisionManager.h"
#include "CSceneManager.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CTransformComponent.h"
#include "CColliderComponent.h"
//#include 

namespace Framework
{
	std::bitset<(UINT)Enums::eLayerType::Size> CCollisionManager::m_bsCollisionCheck[(UINT)Enums::eLayerType::Size] = {false};
	std::unordered_map<UINT64, bool> CCollisionManager::m_unmapCollisions = {};

	CCollisionManager::CCollisionManager()
	{
	}

	CCollisionManager::~CCollisionManager()
	{
	}

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

	void CCollisionManager::Initialize()
	{
	}

	void CCollisionManager::Release()
	{
	}

	void CCollisionManager::Tick()
	{
		CScene* pScene = CSceneManager::GetCurrentScene();

		for (UINT row = 0; row < (UINT)Enums::eLayerType::Size; row++)
		{
			for (UINT col = 0; col < (UINT)Enums::eLayerType::Size; col++)
			{
				if (m_bsCollisionCheck[row][col])
				{
					CollisionCheck(pScene,(Enums::eLayerType)row, (Enums::eLayerType)col);
				}
			}
		}
	}

	void CCollisionManager::LastTick()
	{
	}

	void CCollisionManager::Render(HDC hdc)
	{
	}

	void CCollisionManager::CollisionCheck(CScene* pScene, Enums::eLayerType left, Enums::eLayerType right)
	{
		const std::list<CGameObject*>& lefts = CSceneManager::GetGameObject(left);
		const std::list<CGameObject*>& rights = CSceneManager::GetGameObject(right);

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


	bool CCollisionManager::BoxCollisionStateUpdate(const CColliderComponent* left,const CColliderComponent* right)
	{
		const CTransformComponent* leftTr = left->GetOwner()->GetComponent<CTransformComponent>();
		const CTransformComponent* rightTr = right->GetOwner()->GetComponent<CTransformComponent>();

		const Maths::Vector2 leftPos = leftTr->GetPos() + left->GetOffset();
		const Maths::Vector2 rightPos = rightTr->GetPos() + right->GetOffset();

		const Maths::Vector2 leftSize = left->GetSize() * 100;
		const Maths::Vector2 rightSize = right->GetSize() * 100;

		if (Maths::Abs(leftPos.GetX() - rightPos.GetX()) < Maths::Abs((leftSize.GetX() + rightSize.GetX()) * 0.5f) &&
			Maths::Abs(leftPos.GetY() - rightPos.GetY()) < Maths::Abs((leftSize.GetY() + rightSize.GetY()) * 0.5f))
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

		const float lenght = (Maths::Vector2(leftCirclePos.GetX() + rightCirclePos.GetX(), leftCirclePos.GetY() + rightCirclePos.GetY())).Length();

		if (lenght <= (leftSize.GetX() + rightSize.GetX()) * 0.5f)
		{
			return true;
		}
		return false;
	}




}
