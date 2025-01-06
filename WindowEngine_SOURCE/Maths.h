
namespace Framework::Maths
{
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

	};
}