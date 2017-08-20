#pragma once

class SData
{
public:
	static const int HEIGTH_CANVAS = 400;
	static const int WIDHT_CANVAS = 700;

	static const int DIAMETER_HOLE = 40;
	static const int THICKNESS_BORDER = 50;

	static const int DIAMETER_BALL = 30;
	static const int RADIUS_BALL = 15;

	static const int BALLS_COUNT = 16;
	static const int HOLES_COUNT = 6;

	static const int START_CUE = 15;
	static const int LENGTH_CUE = 70;
	static const int MAX_CUE_LENGTH = 50;

	static const float DECELERATION()
	{ return 0.025; }
	static const float MIN_SPEED()
	{ return 0.1; }
	static const float MAX_SPEED()
	{ return 7; }
	static const float SOME()
	{ return 0.9977; }

	static const System::Drawing::Color STRIP_COLOR()
	{ return System::Drawing::Color::White; }

	static array<CPoint*>^ HOLES()
	{
		array<CPoint*>^ _holes = gcnew array<CPoint*>(SData::BALLS_COUNT - 1);

		_holes[0] = new CPoint(7, 7);
		_holes[1] = new CPoint(325, 7);
		_holes[2] = new CPoint(653, 7);

		_holes[3] = new CPoint(7, 355);
		_holes[4] = new CPoint(325, 353);
		_holes[5] = new CPoint(653, 353);

		return _holes;
	}

	static array<CPoint*>^ HOLES_CENTER()
	{
		array<CPoint*>^ _holes = gcnew array<CPoint*>(SData::BALLS_COUNT - 1);

		_holes[0] = new CPoint(27, 27);
		_holes[1] = new CPoint(345, 27);
		_holes[2] = new CPoint(673, 27);

		_holes[3] = new CPoint(27, 375);
		_holes[4] = new CPoint(345, 373);
		_holes[5] = new CPoint(673, 373);

		return _holes;
	}
};