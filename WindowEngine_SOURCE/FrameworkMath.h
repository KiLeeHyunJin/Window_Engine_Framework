
namespace Framework::BaseMath
{
	struct Vector2
	{
		float x, y;
		Vector2()
		{
			x = y = 0;
		}
		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
	};
}