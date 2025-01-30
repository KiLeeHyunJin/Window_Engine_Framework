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
		__forceinline Maths::Vector2 CaluatePosition(Vector2 pos)	const	{ return pos - m_vecDistance; }

		inline void SetTarget(CGameObject* pTarget)						{ m_pTarget = pTarget; }
		inline void SetResolution(Maths::Vector2 resolution)			{ m_vecResolution = resolution; }

		friend CGameObject;
	private :
		CCameraComponent();
		virtual ~CCameraComponent();

		// CComponent을(를) 통해 상속됨
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

