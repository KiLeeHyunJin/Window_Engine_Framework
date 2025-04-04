#pragma once
#include <cmath>
#include <windows.h>

namespace Framework//::Maths
{

	namespace Maths
	{

		struct Vector2Int;

		float const PI = 3.142592f; //����Ƽ�� C++ ���� Define���� const�� ����϶�� �ߴµ� 
		//���⼭ �̷��� �Ѵٰ� ũ�� �޶����ڳĸ�, �׷��� ������� �����ϱ�

		template<typename T>
		__inline T Abs(const T rhs) { return rhs > 0 ? rhs : rhs * -1; }

		__inline static float RadianToDegree(const float radian) { return (radian * (180 / PI)); }

#pragma region Vector2 Float
		struct Vector2
		{
#pragma region  Static
			static Vector2 Rotate(Vector2 v, float degree) // ��� ȸ��
			{
				v.Normalize();

				const float radian = (degree / 180.0f) * PI;
				const float cos_f = cosf(radian);
				const float sin_f = sinf(radian);

				const float x = (cos_f * v.x) - (sin_f * v.y);
				const float y = (sin_f * v.x) - (cos_f * v.y);

				return Vector2(x, y);
			}

			static bool Intersects(const Vector2& leftCenter, const Vector2& leftSize, const Vector2& rightCenter, const Vector2& rightSize)
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
			/// ����
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
			/// ����(������ ����)
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

			Vector2() :x(0), y(0) {}
			Vector2(float x, float y) : x(x), y(y)
			{
			}
			Vector2(const Vector2Int& other);// : x(other.x), y(other.y) {}
			//Vector2(int x, int y)		: x((float)x), y((float)y)
			//{}
		/*	explicit Vector2(UINT x, UINT y)	: x((float)x), y((float)y)
			{}*/

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

			Vector2& operator = (const Vector2& rhs)
			{
				this->x = rhs.x;
				this->y = rhs.y;
				return *this;
			}

			Vector2& operator += (const Vector2& rhs)
			{
				x += rhs.x;
				y += rhs.y;
				return *this;
			}

			Vector2& operator -= (const Vector2& rhs)
			{
				x -= rhs.x;
				y -= rhs.y;
				return *this;
			}

			Vector2& operator *= (const Vector2& rhs)
			{
				x *= rhs.x;
				y *= rhs.y;
				return *this;
			}

			Vector2& operator /= (const Vector2& rhs)
			{
				x /= rhs.x;
				y /= rhs.y;
				return *this;
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
			Vector2& operator /= (const T& rhs)
			{
				x /= rhs;
				y /= rhs;
				return *this;
			}

			template<typename T>
			Vector2& operator *= (const T& rhs)
			{
				x *= rhs;
				y *= rhs;
				return *this;
			}



			void Clear()
			{
				x = 0;
				y = 0;
			}

			/// <summary>
			/// �غ� ������ ���� ������ ��
			/// </summary>
			float SqrLength() const
			{
				return (x * x) + (y * y);
			}

			/// <summary>
			/// ������ ����
			/// </summary>
			float Length() const
			{
				return sqrtf(SqrLength());
			}

			/// <summary>
			/// �غ��� ������ ��
			/// </summary>
			float TotalElementSize() const
			{
				return Abs(x) + Abs(y);
			}

			/// <summary>
			/// ����ȭ ��ȯ(���⺤�ͷ� ��ȯ)
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
			/// ����ȭ �� ���� (���� ���� ����)
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
#pragma endregion

#pragma region Vector2 INT
		struct  Vector2Int
		{
			Vector2Int(int _x, int _y) : x(_x),y(_y){}
			Vector2Int() :x(0),y(0){}
			Vector2Int(const Vector2& other);
			Vector2 ConvertVector()
			{
				return Maths::Vector2((float)x, (float)y);
			}

			Vector2Int operator + (const Vector2Int& other)
			{
				int returnX = this->x + other.x;
				int returnY = this->y + other.y;
				return Vector2Int(returnX, returnY);
			}

			Vector2Int operator - (const Vector2Int& other)
			{
				int returnX = this->x - other.x;
				int returnY = this->y - other.y;
				return Vector2Int(returnX, returnY);
			}

			int x;
			int y;

			static Vector2Int One;
			static Vector2Int Zero;

			static Vector2Int Right;
			static Vector2Int Left;
			static Vector2Int Up;
			static Vector2Int Down;
		};
#pragma endregion


	}
	

	
}