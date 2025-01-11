#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
#include "CComponent.h"

namespace Framework
{
	class CComponent;
	class CLayer;
	class CGameObject : public CEntity
	{
	public:
		CGameObject();
		virtual ~CGameObject();

		template<typename T>
		T* AddComponent()
		{
			T* com = new T;
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

		friend CLayer;
	private:
		void Initialize();
		void Tick();
		void LastTick();
		void Render(HDC hdc) const;
		void Release();

		void AddTransform();
		std::vector<CComponent*> m_vecComponents;
	};
}

