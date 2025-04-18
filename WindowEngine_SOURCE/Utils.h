#pragma once
#include "CommonInclude.h"

namespace Framework
{
	namespace Resource
	{
		class CSprite;
	}

	class Utils
	{
	public:
		static void DrawTxt		(HDC hdc, const Maths::Vector2& pos, const std::wstring& str);
		static void DrawLine(HDC hdc, const Maths::Vector2& from, const Maths::Vector2& to);

		static void DrawRect	(HDC hdc, const Maths::Vector2& pos, INT w, INT h);
		static void DrawRect	(HDC hdc, const Maths::Vector2& pos, const Maths::Vector2& size);
		static void DrawCircle	(HDC hdc, const Maths::Vector2& pos, INT radius);

		static void UtilBitBlt(HDC hdc, const Maths::Vector2& start, const Maths::Vector2Int& size, const Resource::CSprite* sprite);
		static void UtilBitBlt	(HDC hdc, const Maths::Vector2& start, const Maths::Vector2& size, const Resource::CSprite* sprite);
		

		static void FlagOn(UINT32& dest, UINT32 target)
		{
			UINT32 temp = 1 << target;
			dest |= temp;
		}

		static void FlagOff(UINT32& dest, UINT32 target)
		{
			UINT32 temp = ~(1 << target);
			dest &= temp;
		}

		__forceinline static bool FlagCheck(UINT32 dest, UINT32 target)
		{	return dest & ( 1 << (UINT32)target );	}
	private:
		Utils();
	};
}
