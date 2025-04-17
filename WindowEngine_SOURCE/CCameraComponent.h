#pragma once
#include "CComponent.h"
#include "math.h"
#include "CRenderManager.h"
#include "Define.h"
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
			if ((resolution.x + scale.x) < pos.x || (scale.x * -1) > pos.x) return false;
			if ((resolution.y + scale.y) < pos.y || (scale.y * -1) > pos.y) return false;
			return true;
		}

		void SetCameraRange(const Maths::Vector2& min, const Maths::Vector2& max);

		void SetFollowRange(const Maths::Vector2& followMin, const Maths::Vector2& followMax) 
		{ m_vecFollowMin = followMin; m_vecFollowMax = followMax; }

		void SetTarget(CActor* pTarget);
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

		//bool ClampRange(const Maths::Vector2& target, const Maths::Vector2& min, const Maths::Vector2& max, Maths::Vector2& adjustValue);
		void AdjustDistance(const Maths::Vector2& lookPosition, const Maths::Vector2& resolutionScreen);

		//std::vector<CActor*> m_vecActor;
		//Maths::Vector2 m_vecResolution;

		//Maths::Vector2 m_vecLookPosition;
		Maths::Vector2 m_vecMin			= Maths::Vector2::Zero;
		Maths::Vector2 m_vecMax			= Maths::Vector2::Zero;

		Maths::Vector2 m_vecDistance	= Maths::Vector2::Zero;
		Maths::Vector2 m_vecFollowMin = Maths::Vector2::Zero;
		Maths::Vector2 m_vecFollowMax		= Maths::Vector2::Zero;
		CActor* m_pTarget				= nullptr;
	};

}

