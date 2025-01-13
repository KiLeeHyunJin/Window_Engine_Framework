#pragma once
#include "CComponent.h"
#include "CAnimation.h"
using namespace Framework::Maths;
using namespace Framework::Resource;

namespace Framework
{

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

		void CreateAnimation(const std::wstring& name, CTexture* spriteSheet,
			Vector2 leftTop, Vector2 size, Vector2 offset,
			UINT spriteLength, float duration);

		CAnimation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);


	private:
		CAnimation* m_pCurrentAnimation;
		std::map<std::wstring, CAnimation*> m_mapAnimations;
		bool m_bLoop;

		// CComponent을(를) 통해 상속됨
		void Release() override;
	};


}
