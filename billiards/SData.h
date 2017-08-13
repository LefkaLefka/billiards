#pragma once

class SData
{
public:
	static const int HEIGTH_CANVAS = 400;
	static const int WIDHT_CANVAS = 700;
	static const int DIAMETER_HOLE = 40;
	static const int DIAMETER_BALL = 30;
	static const int RADIUS_BALL = 15;
	static const int BALLS_COUNT = 16;

	static const int START_CUE = 15;
	static const int LENGTH_CUE = 70;
	static const int MAX_CUE_LENGTH = 50;

	static const float MIN_SPEED()
	{ return 5;	}
	static const float MAX_SPEED()
	{ return 5;	}

	static const System::Drawing::Color STRIP_COLOR()
	{
		return System::Drawing::Color::White;
	};
};