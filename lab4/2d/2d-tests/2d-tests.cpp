// 2d-tests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "2d-tests.h"

void VerifyDouble(const double value, const double expectedValue)
{
	BOOST_REQUIRE_CLOSE(value, expectedValue, R_EPS);
}

void VerifyPoint(const CPoint &point, double x, double y)
{
	VerifyDouble(point.x, x);
	VerifyDouble(point.y, y);
}

void VerifyPoint(const CPoint &point, const CPoint &expectedPoint)
{
	VerifyDouble(point.x, expectedPoint.x);
	VerifyDouble(point.y, expectedPoint.y);
}

void VerifyLineSegment(const CLineSegment &line, const CPoint &expectedStart, const CPoint &expectedEnd, const std::string &expectedOutlineColor)
{
	VerifyPoint(line.GetStartPoint(), expectedStart);
	VerifyPoint(line.GetEndPoint(), expectedEnd);
	BOOST_CHECK_EQUAL(line.GetOutlineColor(), expectedOutlineColor);
}

void VerifyCircle(const CCircle &circle, const CPoint &expectedCenter, double expectedRadius, const std::string &expectedOutlineColor, const std::string &expectedFillColor)
{
	VerifyPoint(circle.GetCenter(), expectedCenter);
	VerifyDouble(circle.GetRadius(), expectedRadius);
	BOOST_CHECK_EQUAL(circle.GetOutlineColor(), expectedOutlineColor);
	BOOST_CHECK_EQUAL(circle.GetFillColor(), expectedFillColor);
}
