#pragma once
#include "CPoint.h"
#include "SData.h"
#include "Helper.h"

public class Cue
{
public:
	CPoint* CueStart;
	CPoint* CueEnd;

	Cue(CPoint* center, CPoint* mouceCoord, float startCue)
	{	
		CueStart = Helper::PointFromLength(center->X, center->Y,
			mouceCoord->X, mouceCoord->Y,
			startCue);

		CueEnd = Helper::PointFromLength(CueStart->X, CueStart->Y,
			mouceCoord->X, mouceCoord->Y,
			(float)SData::LENGTH_CUE);
	}
};