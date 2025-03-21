#pragma once
#include "CComponent.h"
#include "math.h"

namespace Framework
{
	using namespace Maths;
	class CGameObject;

	class CCameraComponent :
		public CComponent
	{
	public :
		__forceinline Maths::Vector2 CaluatePosition(const Vector2& pos)	const	{ return pos - m_vecDistance; }
		__forceinline bool ScreenInCheck(const Vector2& pos, const Vector2& scale) const 
		{ 
			Vector2 _scale = scale * 0.5f;
			if (m_vecResolution.x + _scale.x < pos.x || _scale.x * -1 > pos.x) return false;
			if (m_vecResolution.y + _scale.y < pos.y || _scale.y * -1 > pos.y) return false;
			return true;
		}
		inline void SetTarget(CGameObject* pTarget)						{ m_pTarget = pTarget; }
		inline void SetResolution(Maths::Vector2 resolution)			{ m_vecResolution = resolution; }

		static constexpr Enums::eComponentType StaticComponentType() { return Enums::eComponentType::Camera; }
		Enums::eComponentType GetComponentType() const override { return StaticComponentType(); }

		friend CGameObject;
	private :
		CCameraComponent();
		virtual ~CCameraComponent();

		// CComponent��(��) ���� ��ӵ�
		void Initialize() override;
		void Release() override;
		void Tick() override;
		void LastTick() override;
		void Render(HDC hdc) override;

		std::vector<CGameObject*> m_vecGameObject;

		Maths::Vector2 m_vecLookPosition;
		Maths::Vector2 m_vecResolution;
		Maths::Vector2 m_vecDistance;
		CGameObject* m_pTarget;
	};

}

