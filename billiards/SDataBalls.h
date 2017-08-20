#pragma once
#include "Ball.h"
#include "SData.h"
#include "CPoint.h"
#include "vcclr.h"
#include "algorithm"

public ref class SDataBalls
{
public: 
	array<Ball*>^ Balls = gcnew array<Ball*>(SData::BALLS_COUNT);

	SDataBalls()
	{
		Balls[0] = new Ball(*WhiteBallPosition, false, System::Drawing::Color::White);
		Balls[0]->Start = WhiteBallPosition;
		Balls[0]->Speed = 0;
		Balls[0]->End = nullptr;
		Balls[0]->Length = 0;
		Balls[0]->IsVisible = true;

		array<CPoint*>^ _points = MixCoordinates();
		array<System::Drawing::Color>^ colors = Colors();
		array<bool>^ strips = Strips();

		for (int i = 0; i < SData::BALLS_COUNT - 1; ++i)
		{
			Balls[i + 1] = new Ball(*_points[i], strips[i], colors[i]);
			Balls[i + 1]->Speed = 0;
			Balls[i + 1]->End = nullptr;
			Balls[i + 1]->Length = 0;
			Balls[i + 1]->Start = new CPoint(*_points[i]);
			Balls[i + 1]->IsVisible = true;
		}
	};

private:
	array<CPoint*>^ MixCoordinates()
	{
		array<CPoint*>^ _points = Points();

		CPoint point;
		for (int i = 0; i < SData::BALLS_COUNT - 1; ++i)
			std::swap(*_points[i], *_points[std::rand() % (SData::BALLS_COUNT - 1)]);

		return _points;
	};

	static CPoint* WhiteBallPosition = new CPoint(75, 170);

	static array<bool>^ Strips()
	{
		array<bool>^ _strips = gcnew array<bool>(SData::BALLS_COUNT - 1);

		_strips[0] = false;
		_strips[1] = false;
		_strips[2] = false;
		_strips[3] = false;
		_strips[4] = false;

		_strips[5] = false;
		_strips[6] = false;
		_strips[7] = true;
		_strips[8] = true;

		_strips[9] = true;
		_strips[10] = true;
		_strips[11] = true;

		_strips[12] = true;
		_strips[13] = true;

		_strips[14] = false;

		return _strips;
	};

	static array<System::Drawing::Color>^ Colors()
	{
		array<System::Drawing::Color>^ _colors = gcnew array<System::Drawing::Color>(SData::BALLS_COUNT - 1);

		_colors[0] = System::Drawing::Color::Orange;
		_colors[1] = System::Drawing::Color::Violet;
		_colors[2] = System::Drawing::Color::Brown;
		_colors[3] = System::Drawing::Color::Green;
		_colors[4] = System::Drawing::Color::GreenYellow;

		_colors[5] = System::Drawing::Color::Blue;
		_colors[6] = System::Drawing::Color::Red;
		_colors[7] = System::Drawing::Color::Orange;
		_colors[8] = System::Drawing::Color::Violet;

		_colors[9] = System::Drawing::Color::Brown;
		_colors[10] = System::Drawing::Color::Green;
		_colors[11] = System::Drawing::Color::GreenYellow;

		_colors[12] = System::Drawing::Color::Blue;
		_colors[13] = System::Drawing::Color::Red;

		_colors[14] = System::Drawing::Color::Black;
		
		return _colors;
	};

	static array<CPoint*>^ Points()
	{
		array<CPoint*>^ _points = gcnew array<CPoint*>(SData::BALLS_COUNT - 1);

		_points[0] = new CPoint(550, 110);
		_points[1] = new CPoint(550, 140);
		_points[2] = new CPoint(550, 170);
		_points[3] = new CPoint(550, 200);
		_points[4] = new CPoint(550, 230);

		_points[5] = new CPoint(520, 125);
		_points[6] = new CPoint(520, 155);
		_points[7] = new CPoint(520, 185);
		_points[8] = new CPoint(520, 215);
		
		_points[9] = new CPoint(490, 140);
		_points[10] = new CPoint(490, 170);
		_points[11] = new CPoint(490, 200);

		_points[12] = new CPoint(460, 155);
		_points[13] = new CPoint(460, 185);

		_points[14] = new CPoint(430, 170);

		return _points;
	};
};