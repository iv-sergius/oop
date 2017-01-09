#include "stdafx.h"
#include "2d-tests.h"

BOOST_AUTO_TEST_SUITE(LineSegment)
	BOOST_AUTO_TEST_SUITE(constructor)
		BOOST_AUTO_TEST_CASE(create_right_object)
		{
			CPoint point1, point2;
			CLineSegment line(point1, point2, "EEEEEE");
			VerifyLineSegment(line, point1, point2, "eeeeee");
		}
	BOOST_AUTO_TEST_SUITE_END()
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

