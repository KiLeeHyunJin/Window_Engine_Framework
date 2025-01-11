
namespace Framework::Maths
{
	struct Vector2
	{
		static Vector2 One;
		static Vector2 Zero;

		float x;
		float y;

		Vector2():x(0), y(0)
		{	}
		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
		Vector2 operator - ( Vector2 other)
		{
			return Vector2(x - other.x, y - other.y);
		}
		Vector2 operator + (Vector2 other)
		{
			return Vector2(x + other.x, y + other.y);
		}
		template<typename T>
		Vector2 operator / (T other)
		{
			return Vector2(x / other, y / other);
		}
		template<typename T>
		Vector2 operator * (T other)
		{
			return Vector2(x * other, y * other);
		}
	};
}