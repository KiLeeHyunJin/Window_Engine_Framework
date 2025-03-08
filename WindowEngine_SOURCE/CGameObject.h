#pragma once
#include "CommonInclude.h"
#include "CEntity.h"

//������ �߿� �� �θ� Ŭ������ �Լ� ������ ���
//
//�����Լ� ���̺��� ��ġ�� �����Ƿ� �� ���� ȣ�� ������ �����Ѵ�.
//���� ����, �ǽð� ������ �� ������ ���� ����ȭ�� �ʿ��� ��� ����.
//������ ��ü �������� ���谡 ��������� ���������� �������� �� ����.    
//  
// => �Ұ� : �θ� �Լ� �����Ϳ� �ڽ� ��� �Լ��� ������ ����� ����, 
// �ϴ��� �����Լ� ����� �� ���ɰ� ȿ�������� ����
// 
//�ڵ� ���������� �߿� �� ���� �Լ� ���
//
//�������� ���� �����ϰ� �ڵ� ���������� ����.
//������ ���� �߿��� ��찡 �ƴ϶��, �Ϲ����� OOP ���迡���� ���� �Լ��� �� �����ϴ�.

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

