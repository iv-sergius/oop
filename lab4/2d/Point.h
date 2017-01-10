#pragma once
#include "stdafx.h"

class CPoint
{
public:
	CPoint(double x = 0, double y = 0);
	double x;
	double y;
};

double abs(const CPoint &p);
double Distance(const CPoint &p1, const CPoint &p2);
