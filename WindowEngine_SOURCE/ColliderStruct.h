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
		bool Intersects(const Ray& ray, float& tNear) const //Slab 알고리즘
		{
			float tMinX;
			float tMaxX;
			if (ray.direction.x == 0)
			{
				if (ray.origin.x >= min.x && ray.origin.x <= max.x)
					tMinX = tMaxX = ray.origin.x;
				else
					return false;
			}
			else
			{
				tMinX = (min.x - ray.origin.x) / ray.direction.x;
				tMaxX = (max.x - ray.origin.x) / ray.direction.x;
			}

			if (tMinX > tMaxX)
				std::swap(tMinX, tMaxX);

			float tMinY;
			float tMaxY;
			if (ray.direction.y == 0)
			{
				if (ray.origin.y >= min.y && ray.origin.y <= max.y)
					tMinY = tMaxY = ray.origin.y;
				else
					return false;
			}
			else
			{
				tMinY = (min.y - ray.origin.y) / ray.direction.y;
				tMaxY = (max.y - ray.origin.y) / ray.direction.y;
			}

			if (tMinY > tMaxY)
				std::swap(tMinY, tMaxY);

			float tEnter = 
				tMinX > tMinY ? tMinX : tMinY;// max
			float tExit = 
				tMaxX < tMaxY ? tMaxX : tMaxY;//std::min(tMaxX, tMaxY);

			if (tEnter > tExit || tExit < 0)
				return false;

			tNear = tEnter;
			return true;
		}

	private:
		bool IntersectsCheck()
		{

		}
	};
}
