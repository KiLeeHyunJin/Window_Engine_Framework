#pragma once
#include "CComponent.h"
#include "math.h"
#include "CRenderManager.h"

namespace Framework
{
	using namespace Maths;
	class CActor;

	class CCameraComponent :
		public CComponent
	{
	public :
		__forceinline Maths::Vector2 CaluatePosition(const Vector2& pos)	const	
		{
			return pos - m_vecDistance; 
		}

		__forceinline bool ScreenInCheck(const Vector2& pos, const Vector2& scale) const 
		{ 
			//Vector2 _scale = scale * 0.5f;
			const Maths::Vector2Int& resolution = GET_SINGLE(RENDER).GetResolution();
			if (resolution.x + scale.x < pos.x || scale.x * -1 > pos.x) return false;
			if (resolution.y + scale.y < pos.y || scale.y * -1 > pos.y) return false;
			return true;
		}

		void SetCameraRange(const Maths::Vector2& min, const Maths::Vector2& max) { m_vecMin = min; m_vecMax = max; }

		inline void SetTarget(CActor* pTarget)							{ m_pTarget = pTarget;					}
		//inline void SetResolution(Maths::Vector2 resolution)			{ m_vecResolution = resolution;			}

		static constexpr Enums::eComponentType StaticComponentType()	{ return Enums::eComponentType::Camera; }
		const Enums::eComponentType GetComponentType() const override	{ return StaticComponentType();			}

		friend CActor;
	private :
		CCameraComponent();
		virtual ~CCameraComponent();

		// CComponent을(를) 통해 상속됨
		void BeginPlay()			override;
		void Release()				override;
		bool TickComponent()		override;
		bool LastTickComponent()	override;
		void Render(HDC hdc)		override;

		//std::vector<CActor*> m_vecActor;
		//Maths::Vector2 m_vecResolution;

		//Maths::Vector2 m_vecLookPosition;
		Maths::Vector2 m_vecMin		= Maths::Vector2::Zero;
		Maths::Vector2 m_vecMax		= Maths::Vector2::Zero;

		Maths::Vector2 m_vecDistance	= Maths::Vector2::Zero;
		CActor* m_pTarget				= nullptr;
	};

}

