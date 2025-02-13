#pragma once
#include "Maths.h"


namespace Framework
{
	struct Color
	{
		Color()
		{
			this->r = 255;
			this->g = 255;
			this->b = 255;
		}
		BYTE r, g, b;
		Color(BYTE r, BYTE g, BYTE b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
		}
	};



}