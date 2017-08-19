#pragma once
#include "CPoint.h"
#include "SData.h"
#include "vcclr.h"

class Ball : public CPoint
{
public:
	gcroot<System::Drawing::Color> Color;
	bool IsStriped;
	CPoint* Center() 
	{ return new CPoint(X + SData::RADIUS_BALL, Y + SData::RADIUS_BALL); }
	CPoint* End;
	CPoint* Start;
	float Speed;
	float Length;
	bool IsChecked;

	Ball(CPoint point, bool isStrinped, System::Drawing::Color color) : CPoint(point.X, point.Y)
	{
		IsStriped = isStrinped;
		Color = color;
	}

	Ball() { };
};
