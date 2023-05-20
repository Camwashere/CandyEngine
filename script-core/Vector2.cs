using System;

namespace Candy
{
    public struct Vector2
    {
        public float x, y;
        public static Vector2 Zero=> new Vector2(0.0f);

        public Vector2(float scalar)
        {
            x = scalar;
            y = scalar;
        }
        public Vector2(float xValue, yValue)
		{
			x=xValue;
            y=yValue;
		}

		public static Vector2 operator +(Vector2 a, Vector2 b)
		{
			return new Vector2(a.x + b.x, a.y + b.y);
		}

		public static Vector2 operator *(Vector2 vector, float scalar)
		{
			return new Vector2(vector.x * scalar, vector.y * scalar);
		}

		public float LengthSquared()
		{
			return x*x+y*y;
		}

		public float Length()
		{
			return (float)Math.Sqrt(LengthSquared());
		}
    }
}