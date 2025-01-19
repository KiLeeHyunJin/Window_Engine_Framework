#pragma once
#include <cmath>

namespace Framework::Maths
{
#define PI 3.142592f

	struct Vector2
	{
		static Vector2 Rotate(Vector2 v, float degree) // 행렬 회전
		{
			v.Normalize();

			const float radian = (degree / 180.0f) * PI;
			const float cos_f = cosf(radian);
			const float sin_f = sinf(radian);

			const float x = (cos_f * v.x) - (sin_f * v.y);
			const float y = (sin_f * v.x) - (cos_f * v.y);

			return Vector2(x, y);
		}

		/// <summary>
		/// 내적
		/// </summary>
		static float Dot(Vector2& v1, Vector2& v2)
		{
			return (v1.x * v2.x) + (v1.y * v2.y);
		}

		/// <summary>
		/// 외적(수직인 벡터)
		/// </summary>
		static float Cross(Vector2& v1, Vector2& v2)
		{
			return (v1.x * v2.x) - (v1.y * v2.y);
		}


		static Vector2 One;
		static Vector2 Zero;

		static Vector2 Right;
		static Vector2 Left;
		static Vector2 Up;
		static Vector2 Down;

		float x;
		float y;

		Vector2():x(0), y(0)
		{	}
		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2 operator - (Vector2 other)
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

		Vector2 operator / (Vector2 other)
		{
			return Vector2(x / other.x, y / other.y);
		}

		void operator += (Vector2& other)
		{
			x += other.x;
			y += other.y;
		}

		void operator -= (Vector2& other)
		{
			x -= other.x;
			y -= other.y;
		}

		void operator *= (Vector2& other)
		{
			x *= other.x; 
			y *= other.y;
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

		template<typename T>
		void operator /= (T other)
		{
			x /= other;
			y /= other;
		}

		template<typename T>
		void operator *= (T other)
		{
			x *= other;
			y *= other;
		}

		void Clear()
		{
			x = 0;
			y = 0;
		}

		/// <summary>
		/// 빗변의 길이
		/// </summary>
		float Length() const
		{
			return sqrtf((x * x) + (y * y));
		}

		/// <summary>
		/// 빗변의 크기
		/// </summary>
		float SqrLength() const
		{
			return (x * x) + (y * y);
		}

		/// <summary>
		/// 정규화
		/// </summary>
		Vector2 Normalize()
		{
			const float len = Length();
			x /= len;
			y /= len;
			return *this;
		}

		/// <summary>
		/// 정규화 값 생성
		/// </summary>
		Vector2 Normalized() const
		{
			const float len = Length();
			if (len == 0)
			{
				return Vector2::Zero;
			}
			const float x = this->x / len;
			const float y = this->y / len;
			return Vector2(x, y);
		}
	

	};
	template<typename T>
	T Abs(T other)
	{
		return other > 0 ? other : other * -1;
	}

	
}