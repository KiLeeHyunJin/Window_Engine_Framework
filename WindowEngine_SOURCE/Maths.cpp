#include "Maths.h"

namespace Framework//::Maths
{
	namespace Maths
	{
		Vector2 Vector2::One = Vector2(1.0f, 1.0f);
		Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);

		Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
		Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);
		Vector2 Vector2::Up = Vector2(0.0f, -1.0f);
		Vector2 Vector2::Down = Vector2(0.0f, 1.0f);

		Vector2Int Vector2Int::One = Vector2Int(1, 1);
		Vector2Int Vector2Int::Zero = Vector2Int(0, 0);

		Vector2Int Vector2Int::Right = Vector2Int(1, 0);
		Vector2Int Vector2Int::Left = Vector2Int(-1, 0);
		Vector2Int Vector2Int::Up = Vector2Int(0, -1);
		Vector2Int Vector2Int::Down = Vector2Int(0, 1);

		Vector2::Vector2(const Vector2Int& other) : x((float)other.x) , y((float)other.y)	{	}
		Vector2Int::Vector2Int(const Vector2& other) : x((int)other.x), y((int)other.y) {}
	}

}