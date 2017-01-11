#include "stdafx.h"
#include "2d-tests.h"

BOOST_AUTO_TEST_SUITE(LineSegment)
	BOOST_AUTO_TEST_SUITE(constructor)
		BOOST_AUTO_TEST_CASE(create_right_object)
		{
			CPoint point1, point2;
			CLineSegment line(point1, point2, "123456");
			VerifyLineSegment(line, point1, point2, "123456");
			point1 = { 1, 2 };
			point2 = { -4, 3 };
			line = { point1, point2, "EEEEEE" };
			VerifyLineSegment(line, point1, point2, "eeeeee");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetAera)
		BOOST_AUTO_TEST_CASE(always_return_0)
		{
			CPoint point1 = { 1, 2 }, point2 = { -4, 3 };
			CLineSegment line(point1, point2, "123456");
			VerifyDouble(line.GetArea(), 0.);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetPerimeter)
		BOOST_AUTO_TEST_CASE(return_right_value)
		{
			CPoint point1 = { 1, 2 }, point2 = { -3, 5 };
			CLineSegment line(point1, point2, "123456");
			VerifyDouble(line.GetPerimeter(), 5.);
		}
	BOOST_AUTO_TEST_SUITE_END()
/*	BOOST_AUTO_TEST_SUITE(ToString)
		BOOST_AUTO_TEST_CASE(return_right_value)
		{
			CPoint point1 = { 1, 2 }, point2 = { -3, 5 };
			CLineSegment line(point1, point2, "ff00ff");
			BOOST_CHECK_EQUAL(line.ToString(), "LineSegment  1.000 2.000  -3.000 5.000  ff00ff");
		}
	BOOST_AUTO_TEST_SUITE_END()*/

BOOST_AUTO_TEST_SUITE_END()

/*
BOOST_AUTO_TEST_SUITE()
	BOOST_AUTO_TEST_CASE()
	{
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE()
BOOST_AUTO_TEST_SUITE_END()
*/

