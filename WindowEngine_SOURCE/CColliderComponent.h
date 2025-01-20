#pragma once
#include "CComponent.h"

namespace Framework
{
	class CGameObject;
	class CColliderComponent :
		public CComponent
	{
	public:
		inline Maths::Vector2 GetOffset() const { return m_vecOffset; }
		inline void SetOffset(Maths::Vector2 offset) { m_vecOffset = offset; }

	protected:
		CColliderComponent();
		virtual ~CColliderComponent();
		Maths::Vector2 m_vecOffset;

		friend CGameObject;
	private:
		// CComponent을(를) 통해 상속됨
		virtual void Initialize() override;
		virtual void Release() override;
		virtual void Tick() override;
		virtual void LastTick() override;
		virtual void Render(HDC hdc) override;

	};

}


