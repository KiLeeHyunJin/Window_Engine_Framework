#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
#include "CComponent.h"
//#include "CObject.h"

namespace Framework
{
	class CAnimatorComponent;

	class CComponent;
	class CLayer;
	class CGameObject : public CEntity
	{
	public:
		enum class eState
		{
			Played,
			Paused,
			Dead,
			End
		};

		CGameObject();
		virtual ~CGameObject();

		template<typename T>
		T* AddComponent()
		{
			T* getCom = GetComponent<T>();
			if (getCom != nullptr)
			{
				return getCom;
			}
			T* newCom = new T;
			CComponent* const pCom = static_cast<CComponent*>(newCom);

			pCom->Initialize();
			pCom->SetOwner(this);

			const Enums::eComponentType componentType = pCom->GetComponentType();
			m_vecComponents[(int)componentType] = pCom;
			return newCom;
		}

		template<typename T>
		T* GetComponent()
		{
			const T def{};
			const Enums::eComponentType componentType = def.GetComponentType();
			CComponent* pCom = m_vecComponents[(int)componentType];
			T* getCom = dynamic_cast<T*>(pCom);
			return getCom;
		}

		void SetActive(bool power) { m_eState = power ? eState::Played : eState::Paused; }
		eState GetActive() { return m_eState; }
		//friend void Object::Destroy(CGameObject* pObj);
		void Dead();

		friend CLayer;
	private:
		void Initialize();
		void Tick();
		void LastTick();
		void Render(HDC hdc) const;
		void Release();

		void AddTransform();

		std::vector<CComponent*> m_vecComponents;
		eState m_eState;
	};
}

