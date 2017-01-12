#include "stdafx.h"
#include "Point.h"

CPoint::CPoint(double x, double y)
	: x(x), y(y)
{
}

std::string CPoint::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(3)
		<< '(' << x << ", " << y << ')';
	return strm.str();
}

double abs(const CPoint &p)
{
	return sqrt(p.x * p.x + p.y * p.y);
}

double Distance(const CPoint &p1, const CPoint &p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
