#pragma once
#include "CComponent.h"

namespace Framework
{
	class CActor;
	class CColliderComponent :
		public CComponent
	{
	public:
		enum class eColliderType
		{
			Box, Circle, None
		};

		//CColliderComponent();
		virtual ~CColliderComponent();

		CColliderComponent(eColliderType colliderType);

		// CComponent을(를) 통해 상속됨

		virtual void BeginPlay() override;
		virtual void Release() override;

		virtual bool TickComponent() override;
		virtual bool LastTickComponent() override;

		virtual void Render(HDC hdc) override;


		inline const eColliderType GetColliderType()					const	{ return m_eColliderType; }

		inline const UINT32				GetID()							const	{ return m_collId; }
		inline const Maths::Vector2&	GetOffset()						const	{ return m_vecOffset; }
		inline const Maths::Vector2&	GetSize()						const	{ return m_vecSize; }
		inline bool						GetTrigger()					const	{ return m_bTrigger; }
		inline UINT32 GetCollisionFlag()								const	{ return m_iCollisionFlag; }
		inline UINT32 GetColliderID()									const	{ return m_iColliderId; }
		void SetCollisionFlag(INT32 flag)										{ m_iCollisionFlag = flag; }
		inline void						SetOffset(const Maths::Vector2& offset)	{ m_vecOffset = offset; }
		inline void						SetSize(const Maths::Vector2& size)		{ m_vecSize = size; }
		void							SetTrigger(bool state)					{ m_bTrigger = state; }

		virtual void OnCollisionEnter(CColliderComponent* other);
		virtual void OnCollisionStay(CColliderComponent* other);
		virtual void OnCollisionExit(CColliderComponent* other);


		static bool CheckCollisionBoxToBox(CColliderComponent* owner, CColliderComponent* other) ;
		static bool CheckCollisionBoxToCircle(CColliderComponent* owner, CColliderComponent* other);
		static bool CheckCollisionCircleToCircle(CColliderComponent* owner, CColliderComponent* other);

		static constexpr Enums::eComponentType StaticComponentType() { return Enums::eComponentType::Collider; }
		const Enums::eComponentType GetComponentType() const override { return StaticComponentType(); }

		virtual bool CheckCollision(CColliderComponent* other) = 0;

	protected:

		Maths::Vector2 m_vecOffset;
		Maths::Vector2 m_vecSize;

		//friend CActor;
	private:
		
		static UINT32 m_collId;
		UINT32 m_iColliderId;
		UINT32 m_iCollisionFlag;
		eColliderType m_eColliderType;

		bool m_bTrigger;

	};

}


