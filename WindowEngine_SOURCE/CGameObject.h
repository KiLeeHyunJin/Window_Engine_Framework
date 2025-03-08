#pragma once
#include "CommonInclude.h"
#include "CEntity.h"

//성능이 중요 → 부모 클래스의 함수 포인터 사용
//
//가상함수 테이블을 거치지 않으므로 더 빠른 호출 성능을 제공한다.
//게임 엔진, 실시간 렌더링 등 극한의 성능 최적화가 필요한 경우 적합.
//하지만 객체 지향적인 설계가 어려워지고 유지보수가 복잡해질 수 있음.    
//  
// => 불가 : 부모 함수 포인터에 자식 멤버 함수를 대입할 방법이 없고, 
// 하더라도 가상함수 방식이 더 성능과 효율적으로 좋음
// 
//코드 유지보수가 중요 → 가상 함수 사용
//
//다형성을 쉽게 지원하고 코드 유지보수가 쉬움.
//성능이 아주 중요한 경우가 아니라면, 일반적인 OOP 설계에서는 가상 함수가 더 적절하다.

namespace Framework
{
	class CEventManager;
	class CAnimatorComponent;
	class CTransformComponent;
	class CComponent;
	class CLayer;


	class CGameObject : public CEntity
	{
	public:
		enum class eState
		{
			Enable,
			Disable,
		};

		CGameObject(Enums::eLayerType layerType);
		virtual ~CGameObject();

		CTransformComponent* GetTransformComponent() const { return m_pTransform; }
#pragma region  Component Template

		template<typename T>
		T* AddComponent()
		{
			T* getCom = GetComponent<T>();
			if (getCom != nullptr)
			{
				return getCom;
			}
			T* newCom = new T;
			CComponent* pCom = static_cast<CComponent*>(newCom);

			pCom->Initialize();
			pCom->SetOwner(this);

			const Enums::eComponentType componentType = pCom->GetComponentType();
			if (componentType == Enums::eComponentType::Custom)
			{
				m_listCustomComponents.push_back(pCom);
			}
			else
			{
				m_vecComponents[(int)componentType] = pCom;
			}
			return newCom;
		}

		template<typename T>
		T* GetComponent()
		{
			const T def{};
			const Enums::eComponentType componentType = def.GetComponentType();
			T* getCom = nullptr;
			if (componentType == Enums::eComponentType::Custom)
			{
				for (CComponent* pCom : m_listCustomComponents)
				{
					getCom = dynamic_cast<T*>(pCom);
					if (getCom != nullptr)
					{
						return getCom;
					}
				}
			}
			else
			{
				CComponent* pCom = m_vecComponents[(int)componentType];
				if (pCom != nullptr)
				{
					getCom = dynamic_cast<T*>(pCom);
					return getCom;
				}
			}
			return nullptr;
		}

		template<typename T>
		bool RemoveComponent()
		{
			const T def{};
			const Enums::eComponentType componentType = def.GetComponentType();
			if (componentType == Enums::eComponentType::Transform)	{	return false;	}

			if (componentType == Enums::eComponentType::Custom)
			{
				for(auto iter = m_listCustomComponents.cbegin(); 
						 iter != m_listCustomComponents.cend();
						 iter++)
				{
					T* getCom = dynamic_cast<T*>(iter);
					if (getCom != nullptr)
					{
						m_listCustomComponents.erase(iter);
						delete getCom;
						return true;
					}
				}
			}
			else
			{
				CComponent* pCom = m_vecComponents[(int)componentType];
				if (pCom != nullptr)
				{
					m_vecComponents[(int)componentType] = nullptr;
					delete pCom;
					return true;
				}
			}
			return false;
		}

#pragma endregion Component Template

		inline void SetActive(bool power) { m_eState = power ? eState::Enable : eState::Disable; }
		inline void SetLayerType(Enums::eLayerType layerType) { m_eLayerType = layerType; }

		__forceinline const eState GetState()	const { return m_eState; }
		__forceinline const bool GetActive()	const { return m_eState == eState::Enable; }
		//__forceinline const bool GetDead()		const { return m_eState == eState::Destory; }

		__forceinline const Enums::eLayerType GetLayerType() const { return m_eLayerType; }
		__forceinline bool GetReserveDelete() const { return m_bReserveDelete; }

		friend CLayer;
		friend CEventManager;
	private:
		void Initialize();
		void Tick();
		void LastTick();
		void Render(HDC hdc) const;
		void Release();

		//void AddTransform();

		__forceinline void SetSafeToDelete()	{ if (m_bSafeToDelete == false)  m_bSafeToDelete  = true; }
		__forceinline void SetReserveDelete()	{ if (m_bReserveDelete == false) m_bReserveDelete = true; }

		__forceinline bool GetSafeToDelete() const	{ return m_bSafeToDelete; }

		std::vector<CComponent*> m_vecComponents;
		std::list<CComponent*> m_listCustomComponents;

		CTransformComponent* m_pTransform;

		Enums::eLayerType m_eLayerType;
		eState m_eState;

		bool m_bSafeToDelete;
		bool m_bReserveDelete;
	};
}

