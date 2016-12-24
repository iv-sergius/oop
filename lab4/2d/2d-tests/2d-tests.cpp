// 2d-tests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../2d.h"

struct TestPoint
{
	CPoint point;
};

BOOST_FIXTURE_TEST_SUITE(Point_class, TestPoint)
	BOOST_AUTO_TEST_CASE(constuct_0_point_by_default)
	{
		BOOST_CHECK_EQUAL(point.x, 0);
		BOOST_CHECK_EQUAL(point.y, 0);
	}
BOOST_AUTO_TEST_SUITE_END()