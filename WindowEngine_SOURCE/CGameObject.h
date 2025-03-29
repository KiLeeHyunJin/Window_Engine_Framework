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

		CGameObject(UINT layerType);
		virtual ~CGameObject();

		CTransformComponent* GetTransformComponent() const { return m_pTransform; }
#pragma region  Component Template

		template<typename T>
		T* AddComponent()
		{
			static_assert(std::is_base_of<CComponent, T>::value, "T is not from CComponent");

			if (m_bReserveDelete)
				return nullptr;

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
				m_vecCustomComponents.push_back(pCom);
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
			//const T def{};
			static_assert(std::is_base_of<CComponent, T>::value, "T is not from CComponent");
			if (m_bReserveDelete)
				return nullptr;

			const Enums::eComponentType componentType = T::StaticComponentType();
			T* getCom = nullptr;
			if (componentType == Enums::eComponentType::Custom)
			{
				for (CComponent* pCom : m_vecCustomComponents)
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
			//const T def{};
			static_assert(std::is_base_of<CComponent, T>::value, "T is not from CComponent");

			const Enums::eComponentType componentType = T::StaticComponentType();
			if (componentType == Enums::eComponentType::Transform)	{	return false;	}

			if (componentType == Enums::eComponentType::Custom)
			{
				for(auto idx = 0;
					idx != m_vecCustomComponents.size();
					idx++)
				{
					if (m_vecCustomComponents[idx] != nullptr)
					{
						T* getCom = dynamic_cast<T*>(m_vecCustomComponents[idx]);

						if (getCom != nullptr)
						{
							m_vecCustomComponents[idx] = nullptr;
							delete getCom;
							return true;
						}
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

		void ChangeLayer(UINT layerType);

		__forceinline void SetActive(bool power)						{ m_eState = power ? eState::Enable : eState::Disable; }
		__forceinline const UINT GetLayerType()	const	{ return m_eLayerType; }

		//__forceinline const eState GetState()					const	{ return m_eState; }
		__forceinline const bool GetActive()					const	{ return m_eState == eState::Enable; }
		__forceinline const bool GetDisable()					const	{ return m_eState == eState::Disable; }

		__forceinline const bool GetReserveDelete()				const	{ return m_bReserveDelete; }
		__forceinline const bool GetSafeToDelete()				const	{ return m_bSafeToDelete; }
		__forceinline const bool GetDontDestroy()				const	{ return m_bDontDestroy; }
		//__forceinline const bool GetDead()		const { return m_eState == eState::Destory; }


		friend CLayer;
		friend CEventManager;
	private:
		void Initialize();
		void Release();

		bool Tick();
		bool LastTick();
		
		void Render(HDC hdc) const;

		//void AddTransform();

		__forceinline void SetSafeToDelete()								{ if (m_bSafeToDelete == false)  m_bSafeToDelete  = true; }
		__forceinline void SetReserveDelete()								{ if (m_bReserveDelete == false) m_bReserveDelete = true; }
		__forceinline void SetDontDestroy(bool state)						{ m_bDontDestroy = state; }
		__forceinline void SetLayerType(const UINT layerType)				{ if (layerType != m_eLayerType) m_eLayerType = layerType;}
		__forceinline bool RenderCheck() const;
		std::vector<CComponent*> m_vecComponents;
		std::vector<CComponent*> m_vecCustomComponents;

		CTransformComponent* m_pTransform;

		UINT m_eLayerType;
		eState m_eState;

		bool m_bSafeToDelete;
		bool m_bReserveDelete;
		bool m_bDontDestroy;
	};
}

