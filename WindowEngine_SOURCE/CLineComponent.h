#pragma once
#include "CComponent.h"

namespace Framework
{

	class CLineComponent :
		public CComponent
	{
	public:
		CLineComponent();
		virtual ~CLineComponent();
		// CComponent을(를) 통해 상속됨
		const Enums::eComponentType GetComponentType() const override;
		static constexpr Enums::eComponentType	StaticComponentType() { return Enums::eComponentType::Line; }

		void BeginPlay() override;
		void Release() override;
		void Initialize();
		bool TickComponent() override;
		bool LastTickComponent() override;

		void SetLineHeightPercent(float percent)						{ m_fPercent = Maths::Clamp<FLOAT>(percent, 0.05f, 0.95f); }
		__inline const Maths::Vector2&	GetStartPosition()		const	{ return m_vecStartPos;		}
		__inline const Maths::Vector2&	GetEndPosition()		const	{ return m_vecEndPos;		}
		
		//void				SetStartPosition(const Maths::Vector2& startPos)	{ m_vecStartPos = startPos; }
		//void				SetEndPosition(const Maths::Vector2 & endPos)		{	m_vecEndPos = endPos;	}
		bool				CheckCollisionX(float x)			const;
		bool				GetPositionY(float x, float* y)		const;
		bool				GetTrigger()						const	{ return m_bTrigger; }

		void				SetTrigger(bool state) { m_bTrigger = state; }
		void				Render(HDC hdc) override;

		void EventTrigger(float waitTime, bool state);

	private:
		float m_fPercent = 0.1f;
		bool m_bTrigger	 = false;
		Maths::Vector2 m_vecStartPos;
		Maths::Vector2 m_vecEndPos;
		std::pair<FLOAT, BOOL>* m_pTriggerEvent = nullptr;

	};

}
