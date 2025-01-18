#pragma once;
#include <cmath>

namespace Framework::Maths
{
#define PI 3.142592f

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
		Vector2 operator * (Vector2 other)
		{
			return Vector2(x * other.x, y * other.y);
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

		void Clear()
		{
			x = 0;
			y = 0;
		}

		float Length() const
		{
			return sqrtf((x * x) + (y * y));
		}

		Vector2 Normalize()
		{
			const float len = Length();
			x /= len;
			y /= len;
			return *this;
		}

		/// <summary>
	/// ����
	/// </summary>
	/// <param name="v1"></param>
	/// <param name="v2"></param>
		float Dot(Vector2& v1, Vector2& v2)
		{
			return (v1.x * v2.x) + (v1.y * v2.y);
		}

		/// <summary>
		/// ����(������ ����)
		/// </summary>
		/// <param name="v1"></param>����
		/// <param name="v2"></param>����
		float Cross(Vector2& v1, Vector2& v2)
		{
			return (v1.x * v2.x) - (v1.y * v2.y);
		}

		Vector2 Rotate(Vector2 v, float degree) // ��� ȸ��
		{
			v.Normalize();

			const float radian = (degree / 180.0f) * PI;
			const float cos_f = cosf(radian);
			const float sin_f = sinf(radian);

			const float x = (cos_f * v.x) - (sin_f * v.y);
			const float y = (sin_f * v.x) - (cos_f * v.y);

			return Vector2(x, y);
		}

	};

	
}