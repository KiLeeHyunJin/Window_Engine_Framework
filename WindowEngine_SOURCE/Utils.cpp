#include "Utils.h"

namespace Framework
{
	Utils::Utils()
	{	}

	void Utils::DrawTxt(HDC hdc, const Maths::Vector2& pos, const std::wstring& str)
	{
		::TextOut(hdc, 
			static_cast<INT>(pos.x), 
			static_cast<INT>(pos.y), 
			str.c_str(), static_cast<INT>(str.size()));
	}

	void Utils::DrawRect(HDC hdc, const Maths::Vector2& pos, INT w, INT h)
	{
		const float halfX = w * 0.5f;
		const float halfY = h * 0.5f;
		::Rectangle(hdc, 
			static_cast<INT>(pos.x - halfX), 
			static_cast<INT>(pos.y - halfY), 
			static_cast<INT>(pos.x + halfX), 
			static_cast<INT>(pos.y + halfY));
	}

	void Utils::DrawRect(HDC hdc, const Maths::Vector2& pos, const Maths::Vector2& size)
	{
		const float halfX = size.x * 0.5f;
		const float halfY = size.y * 0.5f;
		::Rectangle(hdc,
			static_cast<INT>(pos.x - halfX),
			static_cast<INT>(pos.y - halfY),
			static_cast<INT>(pos.x + halfX),
			static_cast<INT>(pos.y + halfY));
	}

	void Utils::DrawCircle(HDC hdc, const Maths::Vector2& pos, INT radius)
	{
		::Ellipse(hdc, 
			static_cast<INT>(pos.x - radius), 
			static_cast<INT>(pos.y - radius), 
			static_cast<INT>(pos.x + radius), 
			static_cast<INT>(pos.y + radius));
	}

	void Utils::DrawLine(HDC hdc, const Maths::Vector2& from, const Maths::Vector2& to)
	{
		::MoveToEx(hdc, 
			static_cast<INT>(from.x), 
			static_cast<INT>(from.y), nullptr);
		::LineTo(hdc, 
			static_cast<INT>(to.x), 
			static_cast<INT>(to.y));
	}



}