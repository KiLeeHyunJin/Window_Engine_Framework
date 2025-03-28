#pragma once
#include "CommonInclude.h"

namespace Framework
{

	class Utils
	{
	public:
		static void DrawTxt		(HDC hdc, const Maths::Vector2& pos, const std::wstring& str);
		static void DrawLine(HDC hdc, const Maths::Vector2& from, const Maths::Vector2& to);

		static void DrawRect	(HDC hdc, const Maths::Vector2& pos, INT w, INT h);
		static void DrawRect	(HDC hdc, const Maths::Vector2& pos, const Maths::Vector2& size);
		static void DrawCircle	(HDC hdc, const Maths::Vector2& pos, INT radius);


	private:
		Utils();
	};
}
