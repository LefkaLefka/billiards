#pragma once
#include "CPoint.h"
#include "SData.h"
#include "vcclr.h"

class Ball : public CPoint
{
public:
	gcroot<System::Drawing::Color> Color;
	bool IsStriped;
	CPoint* Center = new CPoint(X + SData::RADIUS_BALL, Y + SData::RADIUS_BALL);
	CPoint* End; // must find
	float Speed;

	Ball(CPoint point, bool isStrinped, System::Drawing::Color color) : CPoint(point.X, point.Y)
	{
		IsStriped = isStrinped;
		Color = color;
		//Center = new CPoint(point.X + SData::DIAMETER_BALL / 2, point.Y + SData::DIAMETER_BALL / 2);
	}
	Ball() {};
};
