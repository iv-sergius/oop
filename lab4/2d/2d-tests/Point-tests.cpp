#include "stdafx.h"
#include "2d-tests.h"

BOOST_AUTO_TEST_SUITE(Point_class_constructor)
	BOOST_AUTO_TEST_CASE(make_0_point_by_default)
	{
		CPoint point;
		BOOST_REQUIRE_CLOSE(point.x, 0., R_EPS);
		BOOST_REQUIRE_CLOSE(point.y, 0., R_EPS);
	}
	BOOST_AUTO_TEST_CASE(can_make_custom_point)
	{
		CPoint point(1, 2);
		BOOST_REQUIRE_CLOSE(point.x, 1., R_EPS);
		BOOST_REQUIRE_CLOSE(point.y, 2., R_EPS);
	}
	BOOST_AUTO_TEST_CASE(work_with_initializer_list)
	{
		CPoint point = { 1, 2 };
		BOOST_REQUIRE_CLOSE(point.x, 1., R_EPS);
		BOOST_REQUIRE_CLOSE(point.y, 2., R_EPS);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(abs_function)
	BOOST_AUTO_TEST_CASE(give_correct_value)
	{
		CPoint point;
		BOOST_REQUIRE_CLOSE(abs(point), 0., R_EPS);
		point = { 3, -4 };
		BOOST_REQUIRE_CLOSE(abs(point), 5., R_EPS);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Distance_function)
	BOOST_AUTO_TEST_CASE(give_correct_value)
	{
		CPoint point1, point2;
		BOOST_REQUIRE_CLOSE(Distance(point1,point2), 0., R_EPS);
		point1 = point2 = { 3, -4 };
		BOOST_REQUIRE_CLOSE(Distance(point1, point2), 0., R_EPS);
		point2 = { 7, -1 };
		BOOST_REQUIRE_CLOSE(Distance(point1, point2), 5., R_EPS);
	}
BOOST_AUTO_TEST_SUITE_END()
