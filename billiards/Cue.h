#pragma once
#include "CPoint.h"
#include "Helper.h"
#include "SQuarter.h"

public class Cue
{
public:
	CPoint* CueStart;
	CPoint* CueEnd;

	Cue(CPoint* center, CPoint* mouceCoord, float startCue)
	{	
		CueStart = Helper::StartCue(center->X, center->Y,
			mouceCoord->X, mouceCoord->Y,
			startCue);

		CueEnd = Helper::StartCue(CueStart->X, CueStart->Y,
			mouceCoord->X, mouceCoord->Y,
			(float)SData::LENGTH_CUE);
	}
};