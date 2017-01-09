#pragma once
#include "stdafx.h"

class CPoint
{
public:
	CPoint();
	CPoint(double x, double y);
	double x = 0;
	double y = 0;
};

double abs(const CPoint &p);
double Distance(const CPoint &p1, const CPoint &p2);
