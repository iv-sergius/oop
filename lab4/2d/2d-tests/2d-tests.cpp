// 2d-tests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "2d-tests.h"

void VerifyPoint(const CPoint &point, double x, double y)
{
	BOOST_REQUIRE_CLOSE(point.x, x, R_EPS);
	BOOST_REQUIRE_CLOSE(point.y, y, R_EPS);
}

void VerifyPoint(const CPoint &point, const CPoint &expectedPoint)
{
	BOOST_REQUIRE_CLOSE(point.x, expectedPoint.x, R_EPS);
	BOOST_REQUIRE_CLOSE(point.y, expectedPoint.y, R_EPS);
}

void VerifyLineSegment(const CLineSegment &line, const CPoint &expectedStart, const CPoint &expectedEnd, const std::string &expectedColor)
{
	VerifyPoint(line.GetStartPoint(), expectedStart);
	VerifyPoint(line.GetEndPoint(), expectedEnd);
	BOOST_CHECK_EQUAL(line.GetOutlineColor(), expectedColor);
}