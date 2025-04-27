#pragma once



namespace Framework
{
	struct Color
	{
		Color()
		{
			this->r = 255;
			this->g = 255;
			this->b = 255;
			this->a = 1;
		}
		BYTE r, g, b;
		FLOAT a;
		Color(BYTE r, BYTE g, BYTE b)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = 1;
		}
		Color(BYTE r, BYTE g, BYTE b, FLOAT a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	};



}