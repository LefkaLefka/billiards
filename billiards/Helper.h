#pragma once
#include "Cpoint.h"
#include "SQuarter.h"

class Helper
{
public:
	static CPoint* PointFromLength(float x0, float y0, float x1, float y1, float r)
	{
		SQuarter quarter = Quarter(x0, y0, x1, y1);

		float x = (float)(quarter.X * System::Math::Sqrt((r * r * (x1 - x0) * (x1 - x0)) / (double)((y1 - y0) * (y1 - y0) + (x1 - x0) * (x1 - x0))) + x0);
		float y = (float)((-1 * (-2) * y0 + quarter.Y * System::Math::Sqrt((-2 * y0) * (-2 * y0) - 4 * (y0 * y0 + (x - x0) * (x - x0) - r * r))) / 2.0);

		return new CPoint(x, y);
	}
	static float SpeedFromCue(float length)
	{
		return length * (SData::MAX_SPEED() - SData::MIN_SPEED()) / (SData::MAX_CUE_LENGTH - SData::START_CUE);
	}
	static void ReCalculate(array<Ball*>^ balls)
	{
		//Balls[0]->X += Balls[0]->Speed;
		if (balls[0]->End != nullptr)
		{
			balls[0]->X = balls[0]->End->X;
			balls[0]->Y = balls[0]->End->Y;
		}
		

		//
		//
		//
		//
		//
		//
	}
	static CPoint* EndOfLine(CPoint* startCue, CPoint* ballCenter, CPoint* ballEnd)
	{
		float x, y, t;

		if (startCue->X < ballCenter->X)
		{
			if (startCue->Y > ballCenter->Y)
			{
				if ((startCue->X - ballCenter->X) / (SData::WIDHT_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0 - ballCenter->X) >
					(startCue->Y - ballCenter->Y) / (SData::THICKNESS_BORDER / 2.0 - ballCenter->Y))
				{
					y = SData::THICKNESS_BORDER / 2.0;
					t = (y - startCue->Y) / (ballCenter->Y - startCue->Y);
					x = startCue->X + (ballCenter->X - startCue->X) * t - SData::RADIUS_BALL;
				}
				else
				{
					x = SData::WIDHT_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0;
					t = (x - startCue->X) / (ballCenter->X - startCue->X);
					y = startCue->Y + (ballCenter->Y - startCue->Y) * t - SData::RADIUS_BALL;
				}
			}
			if (startCue->Y < ballCenter->Y)
			{
				if ((startCue->X - ballCenter->X) / (SData::WIDHT_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0 - ballCenter->X) >
					(startCue->Y - ballCenter->Y) / (SData::HEIGTH_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0 - ballCenter->Y))
				{
					y = SData::HEIGTH_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0;
					t = (y - startCue->Y) / (ballCenter->Y - startCue->Y);
					x = startCue->X + (ballCenter->X - startCue->X) * t - SData::RADIUS_BALL;
				}
				else
				{
					x = SData::WIDHT_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0;
					t = (x - startCue->X) / (ballCenter->X - startCue->X);
					y = startCue->Y + (ballCenter->Y - startCue->Y) * t - SData::RADIUS_BALL;
				}
			}				
		}

		if (startCue->X > ballCenter->X)
		{
			if (startCue->Y > ballCenter->Y)
			{
				if ((startCue->X - ballCenter->X) / (SData::THICKNESS_BORDER / 2.0 - ballCenter->X) >
					(startCue->Y - ballCenter->Y) / (SData::THICKNESS_BORDER / 2.0 - ballCenter->Y))
				{
					y = SData::THICKNESS_BORDER / 2.0;
					t = (y - startCue->Y) / (ballCenter->Y - startCue->Y);
					x = startCue->X + (ballCenter->X - startCue->X) * t - SData::RADIUS_BALL;
				}
				else
				{
					x = SData::THICKNESS_BORDER / 2.0;
					t = (x - startCue->X) / (ballCenter->X - startCue->X);
					y = startCue->Y + (ballCenter->Y - startCue->Y) * t - SData::RADIUS_BALL;
				}
			}
			if (startCue->Y < ballCenter->Y)
			{
				if ((startCue->X - ballCenter->X) / (SData::THICKNESS_BORDER / 2.0 - ballCenter->X) >
					(startCue->Y - ballCenter->Y) / (SData::HEIGTH_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0 - ballCenter->Y))
				{
					y = SData::HEIGTH_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0;
					t = (y - startCue->Y) / (ballCenter->Y - startCue->Y);
					x = startCue->X + (ballCenter->X - startCue->X) * t - SData::RADIUS_BALL;
				}
				else
				{
					x = SData::THICKNESS_BORDER / 2.0;
					t = (x - startCue->X) / (ballCenter->X - startCue->X);
					y = startCue->Y + (ballCenter->Y - startCue->Y) * t - SData::RADIUS_BALL;
				}
			}
		}

		if (startCue->X == ballCenter->X)
		{
			if (startCue->Y > ballCenter->Y)
			{
				y = SData::THICKNESS_BORDER / 2.0;
				t = (y - startCue->Y) / (ballCenter->Y - startCue->Y);
				x = startCue->X + (ballCenter->X - startCue->X) * t - SData::RADIUS_BALL;
			}
			if (startCue->Y < ballCenter->Y)
			{
				y = SData::HEIGTH_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0;
				t = (y - startCue->Y) / (ballCenter->Y - startCue->Y);
				x = startCue->X + (ballCenter->X - startCue->X) * t - SData::RADIUS_BALL;
			}
		}

		if (startCue->Y == ballCenter->Y)
		{
			if (startCue->X > ballCenter->X)
			{
				x = SData::THICKNESS_BORDER / 2.0;
				t = (x - startCue->X) / (ballCenter->X - startCue->X);
				y = startCue->Y + (ballCenter->Y - startCue->Y) * t - SData::RADIUS_BALL;
			}
			if (startCue->X < ballCenter->X)
			{
				x = SData::WIDHT_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0;
				t = (x - startCue->X) / (ballCenter->X - startCue->X);
				y = startCue->Y + (ballCenter->Y - startCue->Y) * t - SData::RADIUS_BALL;
			}
		}

		if (x >= SData::THICKNESS_BORDER / 2.0 && 
			x <= SData::WIDHT_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0 &&
			y >= SData::THICKNESS_BORDER / 2.0 &&
			y <= SData::HEIGTH_CANVAS - SData::DIAMETER_BALL - SData::THICKNESS_BORDER / 2.0)
			return new CPoint(x, y);

		return ballEnd;
	}
private:
	static SQuarter Quarter(float x0, float y0, float x, float y)
	{
		SQuarter quarter;

		// 1
		if (x >= x0 && y <= y0)
		{
			quarter.X = 1;
			quarter.Y = -1;
			return quarter;
		}

		// 2
		if (x < x0 && y < y0)
		{
			quarter.X = -1;
			quarter.Y = -1;
			return quarter;
		}

		// 3
		if (x <= x0 && y >= y0)
		{
			quarter.X = -1;
			quarter.Y = 1;
			return quarter;
		}

		// 4
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