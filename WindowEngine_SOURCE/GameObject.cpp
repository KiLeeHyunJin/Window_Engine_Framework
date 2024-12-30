#include "GameObject.h"

namespace Framework
{
	GameObject::GameObject()
	{
		m_fX = 0;
		m_fY = 0;
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::SetPosition(float x, float y)
	{
		m_fX = x;
		m_fY = y;
	}
	float GameObject::GetPositionX()
	{
		return m_fX;
	}
	float GameObject::GetPositionY()
	{
		return m_fY;
	}
}