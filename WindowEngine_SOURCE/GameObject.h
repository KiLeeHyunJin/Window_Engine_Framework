#pragma once

namespace Framework
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void SetPosition(float x, float y);
		float GetPositionX();
		float GetPositionY();

	private:

		float m_fX;
		float m_fY;
	};
}

