#pragma once
#include "CComponent.h"

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
	};
}


