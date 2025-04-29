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
		/// ��ġ �� ȣ��
		/// </summary>
		void Initialize()			override;
		/// <summary>
		/// ��ġ �� ȣ��
		/// </summary>
		void BeginPlay()			override;
		/// <summary>
		/// ���� �� ȣ��
		/// </summary>
		void Release()				override;
		/// <summary>
		/// 1�ʿ� 80�� ȣ��
		/// </summary>
		/// <returns>false�� ��ȯ �� ���� ����</returns>
		bool Tick()					override;
		/// <summary>
		/// Tick ���� �����ϴ� �Լ�
		/// </summary>
		/// <returns>false�� ��ȯ �� ���� ����</returns>
		bool LastTick()				override;
		/// <summary>
		/// �浹 ���� ȣ��
		/// </summary>
		void FixedTick()			override;
		/// <summary>
		/// FixedTick ���� ȣ��
		/// </summary>
		bool Render(HDC hdc) const	override;

	private:
		Resource::CSprite* m_pSprite;
	};


}

