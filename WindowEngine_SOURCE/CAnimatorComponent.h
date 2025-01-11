#pragma once
#include "CComponent.h"
#include "CAnimation.h"

namespace Framework
{
	using namespace Maths;
	using namespace Resource;

	class Resource::CAnimation;

	class CAnimatorComponent :
public CComponent
	{
	public:
		CAnimatorComponent();
		virtual ~CAnimatorComponent();

		void Initialize() override;
		void Tick() override;
		void LastTick()override;

		void Render(HDC hdc)override;

		void CreateAnimation(const std::wstring& name, Resource::CTexture* spriteSheet, 
			Vector2 leftTop, Vector2 size, Vector2 offset,
			UINT spriteLength, float duration);

		CAnimation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);


	private:
		CAnimation* m_pCurrentAnimation;
		std::map<std::wstring, CAnimation> m_mapAnimations;
		bool m_bLoop;
	};


}
