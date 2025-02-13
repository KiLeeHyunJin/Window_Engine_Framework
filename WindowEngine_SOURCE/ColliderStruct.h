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



        bool Intersects(const Ray& ray, float& tNear) const // Slab 알고리즘 (개선됨)
        {
            const float epsilon = 1e-6f; // 0으로 나누는 문제 방지

            // X 방향이 0인 경우
            if (std::abs(ray.direction.x) < epsilon)
            {
                if (ray.origin.x < min.x || ray.origin.x > max.x)
                    return false;

                // Y축 충돌 검사
                float tminY = (min.y - ray.origin.y) / ray.direction.y;
                float tmaxY = (max.y - ray.origin.y) / ray.direction.y;
                if (tminY > tmaxY) std::swap(tminY, tmaxY);

                tNear = tminY;
                return tmaxY >= 0; //  내부에서 시작하는 경우도 포함
            }

            // Y 방향이 0인 경우
            if (std::abs(ray.direction.y) < epsilon)
            {
                if (ray.origin.y < min.y || ray.origin.y > max.y)
                    return false;

                // X축 충돌 검사
                float tminX = (min.x - ray.origin.x) / ray.direction.x;
                float tmaxX = (max.x - ray.origin.x) / ray.direction.x;
                if (tminX > tmaxX) std::swap(tminX, tmaxX);

                tNear = tminX;
                return tmaxX >= 0; //  내부에서 시작하는 경우도 포함
            }

            // 일반적인 Slab 교차 지점 계산
            float tminX = (min.x - ray.origin.x) / ray.direction.x;
            float tmaxX = (max.x - ray.origin.x) / ray.direction.x;
            float tminY = (min.y - ray.origin.y) / ray.direction.y;
            float tmaxY = (max.y - ray.origin.y) / ray.direction.y;

            if (tminX > tmaxX) std::swap(tminX, tmaxX);
            if (tminY > tmaxY) std::swap(tminY, tmaxY);

            // tNear: 처음 충돌하는 거리, tFar: 박스를 통과한 후의 거리
            float tMinTemp = tminX > tminY ? tminX : tminY;
            float tMaxTemp = tmaxX < tmaxY ? tmaxX : tmaxY;

            //  내부에서 시작하는 경우를 허용하기 위해 `tMinTemp < 0` 조건 제거
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
