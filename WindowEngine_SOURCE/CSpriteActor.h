#pragma once
#include "CommonInclude.h"
#include "CActor.h"
#include "CSprite.h"

namespace Framework
{
	class CSpriteActor : public CActor
	{
		DECLARE_PARENT(CActor)
	public:
		CSpriteActor(UINT layer);
		virtual ~CSpriteActor();

		void SetSprite( const Resource::CSprite* pSprite) { m_pSprite = const_cast<Resource::CSprite*>(pSprite); }

	protected:
		/// <summary>
		/// 배치 전 호출
		/// </summary>
		void Initialize()			override;
		/// <summary>
		/// 배치 후 호출
		/// </summary>
		void BeginPlay()			override;
		/// <summary>
		/// 제거 전 호출
		/// </summary>
		void Release()				override;
		/// <summary>
		/// 1초에 80번 호출
		/// </summary>
		/// <returns>false를 반환 시 삭제 예약</returns>
		bool Tick()					override;
		/// <summary>
		/// Tick 이후 실행하는 함수
		/// </summary>
		/// <returns>false를 반환 시 삭제 예약</returns>
		bool LastTick()				override;
		/// <summary>
		/// 충돌 직전 호출
		/// </summary>
		void FixedTick()			override;
		/// <summary>
		/// FixedTick 이후 호출
		/// </summary>
		bool Render(HDC hdc) const	override;

	private:
		Resource::CSprite* m_pSprite;
	};


}

