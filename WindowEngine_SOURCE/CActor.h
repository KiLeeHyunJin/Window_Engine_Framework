#pragma once
#include "CommonInclude.h"
#include "CEntity.h"


namespace Framework
{
	namespace Manager
	{
		class CEventManager;
	}
	class CAnimatorComponent;
	class CTransformComponent;
	class CColliderComponent;
	class CComponent;
	class CLayer;


	class CActor : public CEntity
	{
	public:
		enum class eState
		{
			Enable,
			Disable,
		};

		CActor(UINT layerType);
		virtual ~CActor();

		/// <summary>
		/// 기록 후 배치 전 호출
		/// </summary>
		virtual void Initialize()			= 0;

		/// <summary>
		/// 필드 배치 후 호출
		/// </summary>
		virtual void BeginPlay()			= 0;

		/// <summary>
		/// 제거 전 호출
		/// </summary>
		virtual void Release()				= 0;

		/// <summary>
		/// 1초에 80번 호출
		/// </summary>
		/// <returns>false를 반환 시 삭제 예약</returns>
		virtual bool Tick()					= 0;


		/// <summary>
		/// Tick 이후 실행하는 함수
		/// </summary>
		/// <returns>false를 반환 시 삭제 예약</returns>
		virtual bool LastTick()				= 0;

		/// <summary>
		/// 충돌 직전 호출
		/// </summary>
		virtual void FixedTick()			= 0;

		/// <summary>
		/// FixedTick 이후 호출
		/// </summary>
		/// <param name="hdc"></param>
		virtual bool Render(HDC hdc) const	= 0;

		virtual void OnCollisionEnter(CColliderComponent* other)	{}
		virtual void OnCollisionStay(CColliderComponent* other)		{}
		virtual void OnCollisionExit(CColliderComponent* other)		{}

						void	AddChildID(UINT pActorID);
						void	SetParentID(UINT parentID)				{ m_uiParentID = parentID; }
		__forceinline	UINT	GetParentID()					const	{ return m_uiParentID; }
		__forceinline	UINT	GetChildCount()					const	{ return (UINT)m_vecChilds.size(); }
		__forceinline	UINT	GetChildID(UINT childNum)		const	{ return m_vecChilds[childNum]; }
						void	RemoveChild(UINT childID);
						void	ChangeLayer(UINT layerType);

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

			//pCom->BeginPlay();
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

			const Enums::eComponentType componentType = T::StaticComponentType(); //정적함수를 통해 가져온다.
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
			if (componentType == Enums::eComponentType::Transform)	  
			{	return false;	}

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


		__forceinline const UINT			GetLayerType()		const	{ return m_eLayerType;										}

		__forceinline const bool			GetActive()			const	{ return m_eState == eState::Enable;						}
		__forceinline const bool			GetDisable()		const	{ return m_eState == eState::Disable;						}
		__forceinline		UINT32			GetID()				const	{ return m_uiID;											}

		__forceinline const bool			GetReserveDelete()	const	{ return m_bReserveDelete;									}
		__forceinline const bool			GetSafeToDelete()	const	{ return m_bSafeToDelete;									}
		__forceinline const bool			GetDontDestroy()	const	{ return m_bDontDestroy;									}
		//__forceinline const bool GetDead()		const { return m_eState == eState::Destory; }

		__forceinline const Maths::Vector2& GetLocalPosition()	const	{ return m_vecLocalPosition;								}
		__forceinline const Maths::Vector2	GetPosition()		const	{ return m_vecCurWorldPosition;								}
		__forceinline const Maths::Vector2& GetPrevPosition()	const	{ return m_vecPrevWorldPosition;							}
		__forceinline const Maths::Vector2	GetMoveSqrDirection()const	{ return m_vecCurWorldPosition - m_vecPrevWorldPosition;	}

		__forceinline const Maths::Vector2& GetScale()			const	{ return m_vecScale;										}
		__forceinline const float			GetRotate()			const	{ return m_fRotatate;										}
		__forceinline const Maths::Vector2& GetRenderPosition() const	{ return m_vecRenderPosition;								}

		__forceinline void SetActive(bool power)						{ m_eState = power ? eState::Enable : eState::Disable;		}

		__forceinline void SetLocalPosition(const Maths::Vector2& position)		{ m_vecLocalPosition = position; }
		__forceinline void SetScale(const Maths::Vector2& scale)		{ m_vecScale = scale;										}
		__forceinline void SetRotate(const float rotate)				{ m_fRotatate = rotate;										}

		void SetSafeToDelete()											{ if (m_bSafeToDelete == false)  m_bSafeToDelete = true;	}
		void SetReserveDelete()											{ if (m_bReserveDelete == false) m_bReserveDelete = true;	}
		void SetDontDestroy(bool state)									{ m_bDontDestroy = state;									}
		void SetLayerType(const UINT layerType)							{ if (layerType != m_eLayerType) m_eLayerType = layerType;	}
		void SetID(UINT32 newID)										{ m_uiID = newID;											}


		//friend CLayer;
		//friend Manager::CEventManager;
	protected:
		bool GetRenderCheck()										const	{ return m_bRenderResult; }

	private:
		void CalculatePosition();
		void CalculateRenderPosition();

		Maths::Vector2 m_vecCurWorldPosition;	//절대좌표 (자신 좌표 + 부모 좌표)
		Maths::Vector2 m_vecRenderPosition;		//렌더링 좌표 (카메라 기준 좌표)

		Maths::Vector2 m_vecLocalPosition;			//부모기준 좌표(부모로부터 떨어져있는 위치)
		Maths::Vector2 m_vecPrevWorldPosition;	//이전 프레임 절대좌표
		Maths::Vector2 m_vecScale;
		float m_fRotatate;

		UINT m_eLayerType;
		UINT32 m_uiID;
		eState m_eState;
		UINT m_uiParentID = 0;

		std::vector<UINT> m_vecChilds;
		std::vector<CComponent*> m_vecComponents;
		std::vector<CComponent*> m_vecCustomComponents;

		bool m_bSafeToDelete			= false;
		bool m_bReserveDelete			= false;
		bool m_bDontDestroy				= false;
		bool m_bRenderResult			= false;

	};
}

