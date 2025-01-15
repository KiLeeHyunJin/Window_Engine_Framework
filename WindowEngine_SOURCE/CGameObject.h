#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
#include "CComponent.h"
//#include "CObject.h"

namespace Framework
{
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
			T* com = GetComponent<T>();
			if (com != nullptr)
				return com;
			com = new T;
			CComponent* pCom = static_cast<CComponent*>(com);
			pCom->Initialize();
			pCom->SetOwner(this);
			Enums::eComponentType componentType = pCom->GetComponentType();
			m_vecComponents[(int)componentType] = pCom;
			return com;
		}

		template<typename T>
		T* GetComponent()
		{
			for (CComponent* pCom: m_vecComponents)
			{
				T* com = dynamic_cast<T*>(pCom);
				if (com != nullptr)
				{
					return com;
				}
			}
			return nullptr;
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

