#pragma once
#include "Maths.h"

namespace Framework
{

	struct Ray
	{
		Ray(){}
		Ray(Maths::Vector2 _origin, Maths::Vector2 _dir) : origin(_origin), direction(_dir)
		{};
		Maths::Vector2 origin, direction;
		Ray(const Maths::Vector2& origin, const Maths::Vector2& dest) : origin(origin), direction(dest) {}
	};

	struct Rect
	{
		Maths::Vector2 min, max;

        bool intersects(const Ray& ray, float& tNear) const
        {
            const float epsilon = 1e-6f; 

            if (std::abs(ray.direction.x) < epsilon)
            {
                if (ray.origin.x < min.x || ray.origin.x > max.x)
                    return false;
            }

            if (std::abs(ray.direction.y) < epsilon)
            {
                if (ray.origin.y < min.y || ray.origin.y > max.y)
                    return false;
            }

            float tminX = (min.x - ray.origin.x) / ray.direction.x;
            float tmaxX = (max.x - ray.origin.x) / ray.direction.x;
            float tminY = (min.y - ray.origin.y) / ray.direction.y;
            float tmaxY = (max.y - ray.origin.y) / ray.direction.y;

            if (tminX > tmaxX)
            {
                std::swap(tminX, tmaxX);
            }
            if (tminY > tmaxY)
            {
                std::swap(tminY, tmaxY);
            }

            float tNearTemp = tminX > tminY ? tminX : tminY;
            float tFar      = tmaxX < tmaxY ? tmaxX : tmaxY;

            if (tFar < 0 || 
                tNearTemp > tFar || 
                tNearTemp < 0) 
                return false;

            tNear = tNearTemp;
            return true;
        }



        bool Intersects(const Ray& ray, float& tNear) const // Slab �˰��� (������)
        {
            const float epsilon = 1e-6f; // 0���� ������ ���� ����

            // X ������ 0�� ���
            if (std::abs(ray.direction.x) < epsilon)
            {
                if (ray.origin.x < min.x || ray.origin.x > max.x)
                    return false;

                // Y�� �浹 �˻�
                float tminY = (min.y - ray.origin.y) / ray.direction.y;
                float tmaxY = (max.y - ray.origin.y) / ray.direction.y;
                if (tminY > tmaxY) std::swap(tminY, tmaxY);

                tNear = tminY;
                return tmaxY >= 0; //  ���ο��� �����ϴ� ��쵵 ����
            }

            // Y ������ 0�� ���
            if (std::abs(ray.direction.y) < epsilon)
            {
                if (ray.origin.y < min.y || ray.origin.y > max.y)
                    return false;

                // X�� �浹 �˻�
                float tminX = (min.x - ray.origin.x) / ray.direction.x;
                float tmaxX = (max.x - ray.origin.x) / ray.direction.x;
                if (tminX > tmaxX) std::swap(tminX, tmaxX);

                tNear = tminX;
                return tmaxX >= 0; //  ���ο��� �����ϴ� ��쵵 ����
            }

            // �Ϲ����� Slab ���� ���� ���
            float tminX = (min.x - ray.origin.x) / ray.direction.x;
            float tmaxX = (max.x - ray.origin.x) / ray.direction.x;
            float tminY = (min.y - ray.origin.y) / ray.direction.y;
            float tmaxY = (max.y - ray.origin.y) / ray.direction.y;

            if (tminX > tmaxX) std::swap(tminX, tmaxX);
            if (tminY > tmaxY) std::swap(tminY, tmaxY);

            // tNear: ó�� �浹�ϴ� �Ÿ�, tFar: �ڽ��� ����� ���� �Ÿ�
            float tMinTemp = tminX > tminY ? tminX : tminY;
            float tMaxTemp = tmaxX < tmaxY ? tmaxX : tmaxY;

            //  ���ο��� �����ϴ� ��츦 ����ϱ� ���� `tMinTemp < 0` ���� ����
            if (tMaxTemp < 0 || tMinTemp > tMaxTemp)
                return false;

            tNear = tMinTemp;
            return true;
        }


	private:
		bool IntersectsCheck()
		{

		}
	};
}
