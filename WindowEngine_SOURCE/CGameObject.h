#pragma once
#include "CommonInclude.h"
#include "CEntity.h"
namespace Framework
{
	class CGameObject : public CEntity
	{
	public:
		CGameObject();
		virtual ~CGameObject();

		void Initialize();
		void Tick();
		void LastTick();
		void Render(HDC hdc) const;
		void Release();

		//void SetPosition(float x, float y) { m_fX = x; m_fY = y; }
		//float GetPositionX() const { return m_fX; }
		//float GetPositionY() const { return m_fY; }

	private:

		float m_fX;
		float m_fY;
	};
}

