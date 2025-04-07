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
			m_pTexture = const_cast<CTexture*>(Framework::CResourceManager::FindTexture(wstrResourceKey));
		};
		void SetSize(Maths::Vector2& scale) { m_vecScale = scale; }

		static constexpr Enums::eComponentType StaticComponentType() { return Enums::eComponentType::SpriteRenderer; }
		const Enums::eComponentType GetComponentType() const override { return StaticComponentType(); }

		friend CActor;
	private:
		CSpriteRendererComponent();
		virtual ~CSpriteRendererComponent();

		// CComponent을(를) 통해 상속됨
		void BeginPlay() override;
		void Release() override;
		bool TickComponent() override;
		bool LastTickComponent() override;
		void Render(HDC hdc) override;

		CTexture* m_pTexture;
		Maths::Vector2 m_vecScale;

	};
}


