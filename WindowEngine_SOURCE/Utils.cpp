
#include "CSprite.h"

namespace Framework
{

	Utils::Utils()
	{	}

	/*void Utils::DrawTxt(HDC hdc, const Maths::Vector2& pos, const std::wstring& str)
	{
		return;
		::TextOut(hdc, 
			static_cast<INT>(pos.x), 
			static_cast<INT>(pos.y), 
			str.c_str(), static_cast<INT>(str.size()));
	}


	void Utils::DrawRect(HDC hdc, const Maths::Vector2& pos, INT w, INT h)
	{
		return;

		const float halfX = w * 0.5f;
		::Rectangle(hdc, 
			static_cast<INT>(pos.x - halfX), 
			static_cast<INT>(pos.y), 
			static_cast<INT>(pos.x + halfX), 
			static_cast<INT>(pos.y + h));
	}

	void Utils::DrawRect(HDC hdc, const Maths::Vector2& pos, const Maths::Vector2& size)
	{
		return;

		const float halfX = size.x * 0.5f;
		::Rectangle(hdc,
			static_cast<INT>(pos.x - halfX),
			static_cast<INT>(pos.y),
			static_cast<INT>(pos.x + halfX),
			static_cast<INT>(pos.y + size.y));
	}

	void Utils::DrawCircle(HDC hdc, const Maths::Vector2& pos, INT radius)
	{
		return;

		::Ellipse(hdc, 
			static_cast<INT>(pos.x - radius), 
			static_cast<INT>(pos.y), 
			static_cast<INT>(pos.x + radius), 
			static_cast<INT>(pos.y + (radius << 1)));
	}

	void Utils::UtilBitBlt(HDC hdc, const Maths::Vector2& start, const Maths::Vector2Int& size, const Resource::CSprite* sprite)
	{
		return;

		HDC srcHdc = sprite->GetHDC();
		const Maths::Vector2Int& leftTop = sprite->GetLeftTop();
		BitBlt(hdc, (INT)start.x, (INT)start.y + size.y, size.x, size.y, srcHdc, leftTop.x, leftTop.y, SRCCOPY);
	}

	void Utils::UtilBitBlt(HDC hdc, const Maths::Vector2& start, const Maths::Vector2& size, const Resource::CSprite* sprite)
	{
		return;

		HDC srcHdc = sprite->GetHDC();
		const Maths::Vector2Int& leftTop = sprite->GetLeftTop();
		BitBlt(hdc, (INT)start.x, (INT)start.y + (INT)size.y, (INT)size.x, (INT)size.y, srcHdc, leftTop.x, leftTop.y, SRCCOPY);
	}

	void Utils::UtilBitBlt(HDC hdc, const Maths::Vector2& start, const Maths::Vector2& size, const Resource::CSprite* sprite, ePivot pivot)
	{
		return;

		INT height = (INT)pivot / 10;	
		INT width = (INT)pivot % 10;	
		if (width < 0)
		{
			width *= -1;
		}
		if (width != 0)
		{
			width = width == 5 ? -1 : 1;
		}

		HDC srcHdc = sprite->GetHDC();
		const Maths::Vector2Int& leftTop = sprite->GetLeftTop();

		BitBlt(hdc, (INT)start.x + (((INT)size.x * 0.5) * width), (INT)start.y + (((INT)size.y * 0.5) * height), (INT)size.x, (INT)size.y, srcHdc, leftTop.x, leftTop.y, SRCCOPY);
	}


	void Utils::DrawLine(HDC hdc, const Maths::Vector2& from, const Maths::Vector2& to)
	{
		return;

		::MoveToEx(hdc, 
			static_cast<INT>(from.x), 
			static_cast<INT>(from.y), nullptr);
		::LineTo(hdc, 
			static_cast<INT>(to.x), 
			static_cast<INT>(to.y));
	}*/



}