#pragma once
#include "CComponent.h"
#include "Utils.h"
#include "CActor.h"
#include "Define.h"

namespace Framework
{
	class CBoxColliderComponent;


	class CColliderComponent :
		public CComponent
	{
	public:
		enum class eColliderType
		{
			Box, Circle, None
		};

		virtual ~CColliderComponent();
		CColliderComponent(eColliderType colliderType);


		static constexpr Enums::eComponentType	StaticComponentType()				{ return Enums::eComponentType::Collider;	}
		const Enums::eComponentType				GetComponentType() const override	{ return StaticComponentType();				}
		// CComponent을(를) 통해 상속됨

		virtual void BeginPlay()			override;
		virtual void Release()				override;

		virtual bool TickComponent()		override;
		virtual bool LastTickComponent()	override;

		virtual void Render(HDC hdc)		override;


		inline const eColliderType GetColliderType()					const	{ return m_eColliderType;					}

		//inline const UINT32				GetNextColliderID()				const	{ return m_collId;							}
		inline const Maths::Vector2&	GetOffset()						const	{ return m_vecOffset;						}
		inline const Maths::Vector2&	GetSize()						const	{ return m_vecSize;							}
		inline const bool				GetTrigger()					const	{ return m_bTrigger;						}
		inline const UINT32				GetCollisionFlag()				const	{ return m_iCollisionFlag;					}
		inline const UINT32				GetColliderID()					const	{ return m_iColliderId;						}
		FLOAT							GetAngle()						const	{ return m_fAngle;							}

		void							AddCollisionFlag(UINT32 flag)			{ Utils::FlagOn(m_iCollisionFlag, flag);	}
		void							RemoveCollisionFlag(UINT32 flag)		{ Utils::FlagOff(m_iCollisionFlag, flag);	}
		void							SetCollisionFlag(UINT32 flag)			{ m_iCollisionFlag = flag;					}
		void							ResetCollisionFlag()					{ m_iCollisionFlag = 0;						}

		void							SetOffset(const Maths::Vector2& offset)	{ m_vecOffset = offset;						}
		void							SetSize(const Maths::Vector2& size)		{ m_vecSize = size;							}
		void							SetTrigger(bool state)					{ m_bTrigger = state;						}
		void							SetAngle(float angle)					{ m_fAngle = angle;							}

		__forceinline void OnCollisionEnter(CColliderComponent* other)	{ AdjustPosition(this, other); GetOwner()->OnCollisionEnter(other); }
		__forceinline void OnCollisionStay(CColliderComponent* other)	{ AdjustPosition(this, other); GetOwner()->OnCollisionStay(other); }
		__forceinline void OnCollisionExit(CColliderComponent* other)	{ GetOwner()->OnCollisionExit(other);		}

		//inline bool				ContainsColliderID(UINT32 colliderID)	const	{ return m_unColls.find(colliderID) != m_unColls.end(); }
		//inline void				InsertColliderID(UINT32 colliderID)				{ m_unColls.insert(colliderID); }
		//inline void				RemoveColliderID(UINT32 colliderID)				{  m_unColls.erase(colliderID);						}

		virtual const bool		CheckCollision(CColliderComponent* other);

	protected:
		static const bool		CheckCollisionBoxToBox(CColliderComponent* owner, CColliderComponent* other);
		static const bool		CheckCollisionBoxToCircle(CColliderComponent* owner, CColliderComponent* other);
		static const bool		CheckCollisionCircleToCircle(CColliderComponent* owner, CColliderComponent* other);

		static void		AdjustPosition(CColliderComponent* target, CColliderComponent* other);
		static void		DiagonalAdjustPosition(const Maths::Vector2& moveSqrDir, const RECT& collisionRect, CBoxColliderComponent* targetBoxCollider, CBoxColliderComponent* otherBoxCollider);
		static void		SimpleAdjustPosition(const RECT& collisionRect, CBoxColliderComponent* targetBoxCollider, CBoxColliderComponent* otherBoxCollider);

		static bool InXCheck(CBoxColliderComponent* target, const float otherX);
		static bool InYCheck(CBoxColliderComponent* target, const float otherY);

		__forceinline static bool CheckFlag(CColliderComponent* owner, CColliderComponent* other)
		{
			return Utils::FlagCheck(owner->GetCollisionFlag(), other->GetOwner()->GetLayerType());
		}


		Maths::Vector2	m_vecOffset		= Maths::Vector2::Zero;
		Maths::Vector2	m_vecSize		= Maths::Vector2::Zero;
		FLOAT			m_fAngle		= 0;

		//friend CActor;
	private:
		//std::unordered_set<UINT32> m_unColls;
		UINT32			m_iColliderId;
		UINT32			m_iCollisionFlag;
		eColliderType	m_eColliderType;
		bool			m_bTrigger;

		static UINT32	m_collId;

	};

}


