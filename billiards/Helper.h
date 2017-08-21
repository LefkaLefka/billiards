#pragma once
#include "CPoint.h"
#include "Ball.h"
#include "Game.h"
#include "SQuarter.h"
#include "HelperGame.h"

#include <cmath>

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
	
	static HelperGame* ReCalculate(array<Ball*>^ balls, HelperGame* helperGame)
	{
		if (BallsStoped(balls) && !helperGame->IsProgress)
		{
			helperGame->IsProgress = true;
		}
		else
		{
			for (int i = 0; i < SData::BALLS_COUNT; ++i)
				if (balls[i]->End != nullptr &&
					balls[i]->Speed > 0 &&
					balls[i]->Length >= 0 &&
					balls[i]->IsVisible)
				{
					CPoint* buff = PointFromLength(balls[i]->Center()->X, balls[i]->Center()->Y, balls[i]->End->X, balls[i]->End->Y, balls[i]->Length);

					// In some cases, we get the result with "-nan(ind)"
					// I don't know why it happens
					// But the next line fix this error
					if (!(buff->X != buff->X || buff->Y != buff->Y))
					{
						balls[i]->X = buff->X - SData::RADIUS_BALL;
						balls[i]->Y = buff->Y - SData::RADIUS_BALL;

						balls[i]->Length = balls[i]->Speed;
						balls[i]->Speed -= SData::DECELERATION();

						CheckBallsInHole(balls, helperGame);
						CalculateBallRepulsion(balls);
						CalculateBorderRepulsion(balls[i]);
					}
					else
					{
						balls[i]->Speed = 0;
					}
				}
				else
				{
					balls[i]->Speed = 0;
					balls[i]->Length = 0;
					balls[i]->End = nullptr;
				}
		}

		return helperGame;
	}

	static CPoint* EndOfLine(CPoint* startPoint, CPoint* intermediatePoint, CPoint* ballEnd)
	{
		float x, y, t;

		if (startPoint->X < intermediatePoint->X)
		{
			if (startPoint->Y > intermediatePoint->Y)
			{
				x = SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
				t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
				y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;

				if (y < SData::THICKNESS_BORDER / 2.0) 
				{
					y = SData::THICKNESS_BORDER / 2.0;
					t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
					x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
				}
			}
			if (startPoint->Y < intermediatePoint->Y)
			{
				y = SData::HEIGTH_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
				t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
				x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
				
				if (x > SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0)
				{
					x = SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
					t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
					y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
				}
			}
			if (startPoint->Y == intermediatePoint->Y)
			{
				if (startPoint->X >= intermediatePoint->X)
				{
					x = SData::THICKNESS_BORDER / 2.0;
					t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
					y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
				}
				if (startPoint->X < intermediatePoint->X)
				{
					x = SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
					t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
					y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
				}
			}
		}

		if (startPoint->X > intermediatePoint->X)
		{
			if (startPoint->Y > intermediatePoint->Y)
			{
				y = SData::THICKNESS_BORDER / 2.0;
				t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
				x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;

				if (x < SData::THICKNESS_BORDER / 2.0)
				{
					x = SData::THICKNESS_BORDER / 2.0;
					t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
					y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
				}
			}
			if (startPoint->Y < intermediatePoint->Y)
			{
				y = SData::HEIGTH_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
				t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
				x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;

				if (x < SData::THICKNESS_BORDER / 2.0)
				{
					x = SData::THICKNESS_BORDER / 2.0;
					t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
					y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
				}
			}
			if (startPoint->Y == intermediatePoint->Y)
			{
				if (startPoint->X >= intermediatePoint->X)
				{
					x = SData::THICKNESS_BORDER / 2.0;
					t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
					y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
				}
				if (startPoint->X < intermediatePoint->X)
				{
					x = SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
					t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
					y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
				}
			}
		}

		if (startPoint->X == intermediatePoint->X)
		{
			if (startPoint->Y >= intermediatePoint->Y)
			{
				y = SData::THICKNESS_BORDER / 2.0;
				t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
				x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
			}
			if (startPoint->Y < intermediatePoint->Y)
			{
				y = SData::HEIGTH_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
				t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
				x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
			}
		}

		//old end of line
		//if (startPoint->X < intermediatePoint->X)
		//{
		//	if (startPoint->Y > intermediatePoint->Y)
		//	{
		//		if ((startPoint->X - intermediatePoint->X) / (SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0 - intermediatePoint->X) >
		//			(startPoint->Y - intermediatePoint->Y) / (SData::THICKNESS_BORDER / 2.0 - intermediatePoint->Y))
		//		{
		//			y = SData::THICKNESS_BORDER / 2.0;
		//			t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
		//			x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
		//		}
		//		else
		//		{
		//			x = SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
		//			t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
		//			y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
		//		}
		//	}
		//	if (startPoint->Y < intermediatePoint->Y)
		//	{
		//		if ((startPoint->X - intermediatePoint->X) / (SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0 - intermediatePoint->X) >
		//			(startPoint->Y - intermediatePoint->Y) / (SData::HEIGTH_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0 - intermediatePoint->Y))
		//		{
		//			y = SData::HEIGTH_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
		//			t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
		//			x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
		//		}
		//		else
		//		{
		//			x = SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
		//			t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
		//			y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
		//		}
		//	}
		//}
		//
		//if (startPoint->X > intermediatePoint->X)
		//{
		//	if (startPoint->Y > intermediatePoint->Y)
		//	{
		//		if ((startPoint->X - intermediatePoint->X) / (SData::THICKNESS_BORDER / 2.0 - intermediatePoint->X) >
		//			(startPoint->Y - intermediatePoint->Y) / (SData::THICKNESS_BORDER / 2.0 - intermediatePoint->Y))
		//		{
		//			y = SData::THICKNESS_BORDER / 2.0;
		//			t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
		//			x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
		//		}
		//		else
		//		{
		//			x = SData::THICKNESS_BORDER / 2.0;
		//			t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
		//			y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
		//		}
		//	}
		//	if (startPoint->Y < intermediatePoint->Y)
		//	{
		//		if ((startPoint->X - intermediatePoint->X) / (SData::THICKNESS_BORDER / 2.0 - intermediatePoint->X) >
		//			(startPoint->Y - intermediatePoint->Y) / (SData::HEIGTH_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0 - intermediatePoint->Y))
		//		{
		//			y = SData::HEIGTH_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
		//			t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
		//			x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
		//		}
		//		else
		//		{
		//			x = SData::THICKNESS_BORDER / 2.0;
		//			t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
		//			y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
		//		}
		//	}
		//}
		//
		//if (startPoint->X == intermediatePoint->X)
		//{
		//	if (startPoint->Y > intermediatePoint->Y)
		//	{
		//		y = SData::THICKNESS_BORDER / 2.0;
		//		t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
		//		x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
		//	}
		//	if (startPoint->Y < intermediatePoint->Y)
		//	{
		//		y = SData::HEIGTH_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
		//		t = (y - startPoint->Y) / (intermediatePoint->Y - startPoint->Y);
		//		x = startPoint->X + (intermediatePoint->X - startPoint->X) * t - SData::RADIUS_BALL;
		//	}
		//}
		//
		//if (startPoint->Y == intermediatePoint->Y)
		//{
		//	if (startPoint->X > intermediatePoint->X)
		//	{
		//		x = SData::THICKNESS_BORDER / 2.0;
		//		t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
		//		y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
		//	}
		//	if (startPoint->X < intermediatePoint->X)
		//	{
		//		x = SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0;
		//		t = (x - startPoint->X) / (intermediatePoint->X - startPoint->X);
		//		y = startPoint->Y + (intermediatePoint->Y - startPoint->Y) * t - SData::RADIUS_BALL;
		//	}
		//}

		/*if (!(x >= SData::THICKNESS_BORDER / 2.0 && 
			x <= SData::WIDHT_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0 &&
			y >= SData::THICKNESS_BORDER / 2.0 &&
			y <= SData::HEIGTH_CANVAS - SData::RADIUS_BALL - SData::THICKNESS_BORDER / 2.0))
		
			return ballEnd;*/

		return new CPoint(x, y);
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

	static void CalculateBorderRepulsion(Ball* ball)
	{
		if (!ball->IsVisible)
			return;

		if (ball->X <= SData::THICKNESS_BORDER / 2.0)
		{
			if (ball->Start->Y <= ball->End->Y)
			{
				float y = ball->End->Y + (ball->End->Y - ball->Start->Y);

				CPoint* buff = EndOfLine(ball->End, new CPoint(ball->Start->X, y), ball->End);

				ball->Start = new CPoint(ball->End->X, ball->End->Y);
				ball->End = buff;
				return;
			}
			if (ball->Start->Y > ball->End->Y)
			{
				float y = ball->End->Y - (ball->Start->Y - ball->End->Y);

				CPoint* buff = EndOfLine(ball->End, new CPoint(ball->Start->X, y), ball->End);

				ball->Start = new CPoint(ball->End->X, ball->End->Y);
				ball->End = buff;
				return;
			}
		}

		if (ball->X + SData::DIAMETER_BALL >= SData::WIDHT_CANVAS - SData::THICKNESS_BORDER / 2.0)
		{
			if (ball->Start->Y <= ball->End->Y)
			{
				float y = ball->End->Y + (ball->End->Y - ball->Start->Y);

				CPoint* buff = EndOfLine(ball->End, new CPoint(ball->Start->X, y), ball->End);

				ball->Start = new CPoint(ball->End->X, ball->End->Y);
				ball->End = buff;
				return;
			}
			if (ball->Start->Y > ball->End->Y)
			{
				float y = ball->End->Y - (ball->Start->Y - ball->End->Y);

				CPoint* buff = EndOfLine(ball->End, new CPoint(ball->Start->X, y), ball->End);

				ball->Start = new CPoint(ball->End->X, ball->End->Y);
				ball->End = buff;
				return;
			}
		}

		if (ball->Y <= SData::THICKNESS_BORDER / 2.0)
		{
			if (ball->Start->X <= ball->End->X)
			{
				float x = ball->End->X + (ball->End->X - ball->Start->X);

				CPoint* buff = EndOfLine(ball->End, new CPoint(x, ball->Start->Y), ball->End);

				ball->Start = new CPoint(ball->End->X, ball->End->Y);
				ball->End = buff;
				return;
			}
			if (ball->Start->X > ball->End->X)
			{
				float x = ball->End->X - (ball->Start->X - ball->End->X);

				CPoint* buff = EndOfLine(ball->End, new CPoint(x, ball->Start->Y), ball->End);

				ball->Start = new CPoint(ball->End->X, ball->End->Y);
				ball->End = buff;
				return;
			}
		}

		if (ball->Y + SData::DIAMETER_BALL >= SData::HEIGTH_CANVAS - SData::THICKNESS_BORDER / 2.0)
		{
			if (ball->Start->X <= ball->End->X)
			{
				float x = ball->End->X + (ball->End->X - ball->Start->X);

				CPoint* buff = EndOfLine(ball->End, new CPoint(x, ball->Start->Y), ball->End);

				ball->Start = new CPoint(ball->End->X, ball->End->Y);
				ball->End = buff;
				return;
			}
			if (ball->Start->X > ball->End->X)
			{
				float x = ball->End->X - (ball->Start->X - ball->End->X);

				CPoint* buff = EndOfLine(ball->End, new CPoint(x, ball->Start->Y), ball->End);

				ball->Start = new CPoint(ball->End->X, ball->End->Y);
				ball->End = buff;
				return;
			}
		}
	}

	static void CalculateBallRepulsion(array<Ball*>^ balls)
	{
		for (int i = 0; i < SData::BALLS_COUNT; ++i)
		{
			if (balls[i]->Speed > 0 && balls[i]->IsVisible)
				for (int j = 0; j < SData::BALLS_COUNT; ++j)
				{
					if (i != j && balls[i]->IsVisible)
					{
						if (balls[j]->IsVisible)
						{
							float centerLength = std::sqrt((balls[i]->Center()->X - balls[j]->Center()->X) *
								(balls[i]->Center()->X - balls[j]->Center()->X) +
								(balls[i]->Center()->Y - balls[j]->Center()->Y) *
								(balls[i]->Center()->Y - balls[j]->Center()->Y));

							if (centerLength <= SData::DIAMETER_BALL)
							{
								CPoint* buff = EndOfLine(balls[i]->Center(), balls[j]->Center(), balls[j]->End);

								balls[i]->End->X = 2 * balls[i]->Center()->X - balls[j]->Center()->X;
								balls[i]->End->Y = 2 * balls[i]->Center()->Y - balls[j]->Center()->Y;
								balls[i]->End = EndOfLine(balls[i]->Center(), balls[i]->End, balls[i]->End);

								balls[j]->End = buff;

								balls[j]->Speed = balls[i]->Speed * SData::SPEED_TRANSFER();
								balls[i]->Speed = balls[i]->Speed * SData::SPEED_TRANSFER();
							}
						}
					}
				}
		}
	}

	static void CheckBallsInHole(array<Ball*>^ balls, HelperGame* helperGame)
	{
		array<CPoint*>^ HOLES_CENTER = SData::HOLES_CENTER();

		for (int i = 0; i < SData::BALLS_COUNT; ++i)
			for (int j = 0; j < SData::HOLES_COUNT; ++j)
				if (balls[i]->IsVisible)
					if (std::sqrt(
						(balls[i]->Center()->X - HOLES_CENTER[j]->X) *
						(balls[i]->Center()->X - HOLES_CENTER[j]->X) +
						(balls[i]->Center()->Y - HOLES_CENTER[j]->Y) *
						(balls[i]->Center()->Y - HOLES_CENTER[j]->Y)) <
						SData::RADIUS_BALL + 5)
					{
						// check what it a ball
						//
						if (balls[i]->Color == System::Drawing::Color::Black)
						{
							helperGame->IsBlack = true;
							helperGame->IsProgress = true;
						}

						if (balls[i]->Color == System::Drawing::Color::White)
						{
							helperGame->SetWhiteBall = true;
							helperGame->IsProgress = true;
						}

						if (!helperGame->IsProgress)
						{
							if (helperGame->Player1->IsProgress)
								++helperGame->Player1->BallsCount;

							if (helperGame->Player2->IsProgress)
								++helperGame->Player2->BallsCount;

							balls[i]->IsVisible = false;
							balls[i]->Speed = 0;
						}
					}
	}

	static bool BallsStoped(array<Ball*>^ balls)
	{
		for (int i = 0; i < SData::BALLS_COUNT; ++i)
			if (balls[i]->Speed > 0)
				return false;

		return true;
	}
};