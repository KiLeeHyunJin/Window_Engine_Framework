#pragma once
#include "CComponent.h"
#include "CTexture.h"
#include "CResourceManager.h"

namespace Framework
{
	using namespace Resource;

	class CSpriteRendererComponent :
		public CComponent
	{
	public:
		inline void SetTexture(const std::wstring& wstrResourceKey)
		{
			m_pTexture = Framework::CResourceManager::Find<CTexture>(wstrResourceKey);
		};
		void SetSize(Maths::Vector2 scale) { m_vecScale = scale; }

		friend CGameObject;
	private:
		CSpriteRendererComponent();
		virtual ~CSpriteRendererComponent();

		// CComponent을(를) 통해 상속됨
		void Initialize() override;
		void Release() override;
		void Tick() override;
		void LastTick() override;
		void Render(HDC hdc) override;

		CTexture* m_pTexture;
		Maths::Vector2 m_vecScale;

	};
}


