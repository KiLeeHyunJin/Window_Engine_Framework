#pragma once
#include "CComponent.h"

namespace Framework
{
	class CGameObject;
	class CColliderComponent :
		public CComponent
	{
	public:
		enum class eColliderType
		{
			Box, Circle, None
		};

		CColliderComponent();
		virtual ~CColliderComponent();

		inline const eColliderType GetColliderType() const { return m_eColliderType; }

		inline const UINT32 GetID()			const { return m_collId; }
		inline const Maths::Vector2& GetOffset()	const { return m_vecOffset; }
		inline const Maths::Vector2& GetSize()		const { return m_vecSize; }

		inline void SetOffset(const Maths::Vector2& offset){ m_vecOffset = offset; }
		inline void SetSize(const Maths::Vector2& size)	{ m_vecSize = size; }

		virtual void OnCollisionEnter(CColliderComponent* other);
		virtual void OnCollisionStay(CColliderComponent* other);
		virtual void OnCollisionExit(CColliderComponent* other);

		static constexpr Enums::eComponentType StaticComponentType() { return Enums::eComponentType::Collider; }
		Enums::eComponentType GetComponentType() const override { return StaticComponentType(); }

	protected:
		CColliderComponent(eColliderType colliderType);

		virtual void Initialize() override;
		virtual void Release() override;

		Maths::Vector2 m_vecOffset;
		Maths::Vector2 m_vecSize;
		UINT32 m_iColliderId;

		friend CGameObject;
	private:

		// CComponent을(를) 통해 상속됨
		
		virtual void Tick() override;
		virtual void LastTick() override;
		virtual void Render(HDC hdc) override;
		static UINT32 m_collId;

		eColliderType m_eColliderType;

	};

}


