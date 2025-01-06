#pragma once
#include "CComponent.h"
#include "CTexture.h"
#include "CResourceManager.h"

namespace Framework
{
	class CSpriteRenderer :
		public CComponent
	{
	public:
		CSpriteRenderer();
		virtual ~CSpriteRenderer();

		// CComponent��(��) ���� ��ӵ�
		void Initialize() override;
		void Release() override;
		void Tick() override;
		void LastTick() override;
		void Render(HDC hdc) override;

		void SetTexture(const std::wstring& wstrResourceKey) 
		{ 
			m_pTexture = CResourceManager::Find<CTexture>(wstrResourceKey);
		};
		void SetSize(Maths::Vector2 scale) { m_vecScale = scale; }

	private :
		CTexture* m_pTexture;
		Maths::Vector2 m_vecScale;

	};
}


