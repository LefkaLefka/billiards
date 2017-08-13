#pragma once
#include "Cpoint.h"
#include "SQuarter.h"

class Helper
{
public:
	static CPoint* StartCue(float x0, float y0, float x1, float y1, float r)
	{
		SQuarter quarter = Quarter(x0, y0, x1, y1);

		float x = (float)(quarter.X * System::Math::Sqrt((r * r * (x1 - x0) * (x1 - x0)) / (double)((y1 - y0) * (y1 - y0) + (x1 - x0) * (x1 - x0))) + x0);
		float y = (float)((-1 * (-2) * y0 + quarter.Y * System::Math::Sqrt((-2 * y0) * (-2 * y0) - 4 * (y0 * y0 + (x - x0) * (x - x0) - r * r))) / 2.0);

		return new CPoint(x, y);
	}
	static float SpeedFromCue(float length)
	{
		return 0;
	}
private:
	static SQuarter Quarter(float x0, float y0, float x, float y)
	{
		SQuarter quarter;

		if (x >= x0 && y <= y0)
		{
			quarter.X = 1;
			quarter.Y = -1;
			return quarter;
		}

		if (x < x0 && y < y0)
		{
			quarter.X = -1;
			quarter.Y = -1;
			return quarter;
		}

		if (x <= x0 && y >= y0)
		{
			quarter.X = -1;
			quarter.Y = 1;
			return quarter;
		}

		if (x > x0 && y > y0)
		{
			quarter.X = 1;
			quarter.Y = 1;
			return quarter;
		}

		quarter.X = 0;
		quarter.Y = 0;

		return quarter;
	};
};