#pragma once
#include <cmath>
#include <windows.h>
namespace Framework::Maths
{
	float const PI = 3.142592f; //이펙티브 C++ 에서 Define보단 const를 사용하라고 했는데 
								//여기서 이렇게 한다고 크게 달라지겠냐만, 그래도 습관들면 좋으니까

	template<typename T>
	T Abs(T rhs)
	{
		return rhs > 0 ? rhs : rhs * -1;
	}

	inline static float RadianToDegree(float radian) { return (radian * (180 / PI)); }

	struct Vector2
	{

#pragma region  Static
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

		static bool Intersects(Vector2 leftCenter, Vector2 leftSize, Vector2 rightCenter, Vector2 rightSize)
		{
			float xDistance = Abs(leftCenter.x - rightCenter.x);
			float xSize = Abs((leftSize.x + rightSize.x) * 0.5f);
			float yDistance = Abs(leftCenter.y - rightCenter.y);
			float ySize = Abs((leftSize.y + rightSize.y) * 0.5f);
			if (xDistance <= xSize &&
				yDistance <= ySize)
			{
				return true;
			}
			return false;
		}

		/// <summary>
		/// 내적
		/// </summary>
		static float Dot(Vector2& v1, Vector2& v2)
		{
			return (v1.x * v2.x) + (v1.y * v2.y);
		}

		static float Dot(const Vector2& v1, const Vector2& v2)
		{
			return (v1.x * v2.x) + (v1.y * v2.y);
		}

		static float Dot(Vector2& v1, const Vector2& v2)
		{
			return (v1.x * v2.x) + (v1.y * v2.y);
		}

		static float Dot(const Vector2& v1, Vector2& v2)
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
#pragma endregion

				 Vector2():x(0), y(0){	}
		explicit Vector2(float x, float y)	: x(x), y(y)
		{}
		explicit Vector2(int x, int y)		: x((float)x), y((float)y)
		{}
		explicit Vector2(UINT x, UINT y)	: x((float)x), y((float)y)
		{}

		bool HasValue() const
		{
			if (this->x != 0.0f)
				return true;
			if (this->y != 0.0f)
				return true;
			return false;
		}

		Vector2 operator - (const Vector2& rhs) const
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}		
		Vector2 operator - () const
		{
			return Vector2(-x, -y);
		}

		Vector2 operator + (const Vector2& rhs) const
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		Vector2 operator * (const Vector2& rhs) const
		{
			return Vector2(x * rhs.x, y * rhs.y);
		}

		Vector2 operator / (const Vector2& rhs) const
		{
			return Vector2(x / rhs.x, y / rhs.y);
		}

		void operator += (const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
		}

		void operator -= (const Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
		}

		void operator *= (const Vector2& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
		}

		void operator /= (const Vector2& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
		}

		bool operator == (const Vector2& rhs)
		{
			if (this->x != rhs.x)
				return false;
			if (this->y != rhs.y)
				return false;
			return true;
		}

		bool operator != (const Vector2& rhs)
		{
			return (*this == rhs) == false;
		}

		template<typename T>
		Vector2 operator + (const T& rhs) const
		{
			return Vector2(x + rhs, y + rhs);
		}

		template<typename T>
		Vector2 operator - (const T& rhs) const
		{
			return Vector2(x - rhs, y - rhs);
		}

		template<typename T>
		Vector2 operator / (const T& rhs) const
		{
			return Vector2(x / rhs, y / rhs);
		}

		template<typename T>
		Vector2 operator * (const T& rhs) const
		{
			return Vector2(x * rhs, y * rhs);
		}

		template<typename T>
		void operator /= (const T& rhs)
		{
			x /= rhs;
			y /= rhs;
		}

		template<typename T>
		void operator *= (const T& rhs)
		{
			x *= rhs;
			y *= rhs;
		}

		void Clear()
		{
			x = 0;
			y = 0;
		}

		/// <summary>
		/// 밑변 제곱과 높이 제곱의 합
		/// </summary>
		float SqrLength() const
		{
			return (x * x) + (y * y);
		}

		/// <summary>
		/// 빗변의 길이
		/// </summary>
		float Length() const
		{
			return sqrtf(SqrLength());
		}

		/// <summary>
		/// 밑변과 높이의 합
		/// </summary>
		float TotalElementSize() const
		{
			return Abs(x) + Abs(y);
		}

		/// <summary>
		/// 정규화 변환(방향벡터로 변환)
		/// </summary>
		Vector2 Normalize()
		{
			const float size = TotalElementSize();
			if (size == 0.0f)
			{
				return *this;
			}
			const float len = Length();
			if (len == 1.0f)
			{
				return *this;
			}
			this->x /= len;
			this->y /= len;
			return *this;
		}

		/// <summary>
		/// 정규화 값 생성 (방향 벡터 생성)
		/// </summary>
		Vector2 Normalized() const
		{
			const float size = TotalElementSize();
			if (size == 0.0f)
			{
				return Vector2::Zero;
			}
			const float len = Length();
			if (len == 1.0f)
			{
				return Vector2(this->x, this->y);
			}
			const float _x = this->x / len;
			const float _y = this->y / len;
			return Vector2(_x, _y);
		}


			float x;
			float y;
	};
	

	
}