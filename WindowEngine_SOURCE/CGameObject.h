#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
#include "CComponent.h"

namespace Framework
{
	class CComponent;

	class CGameObject : public CEntity
	{
	public:
		CGameObject();
		virtual ~CGameObject();

		void Initialize();
		void Tick();
		void LastTick();
		void Render(HDC hdc) const;
		void Release();

		template<typename T>
		T* AddComponent()
		{
			T* com = new T;
			CComponent* pCom = static_cast<CComponent*>(com);
			pCom->SetOwner(this);
			m_vecComponent.push_back(pCom);
			return com;
		}

		template<typename T>
		T* GetComponent()
		{
			for (CComponent* pCom: m_vecComponent)
			{
				T* com = dynamic_cast<T*>(pCom);
				if (com != nullptr)
				{
					return com;
				}
			}
			return nullptr;
		}

	private:

		vector<CComponent*> m_vecComponent;
	};
}

