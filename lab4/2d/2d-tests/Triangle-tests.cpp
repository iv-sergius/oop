#include "stdafx.h"
#include "2d-tests.h"

BOOST_AUTO_TEST_SUITE(Triangle)
	BOOST_AUTO_TEST_SUITE(constructor)
		BOOST_AUTO_TEST_CASE(create_right_object)
		{
			CPoint point1, point2, point3;
			CTriangle triangle(point1, point2, point3, "000000", "000000");
			VerifyTriangle(triangle, { 0., 0. }, { 0., 0. }, { 0., 0. }, "000000", "000000");

			point1 = { 1., 2. };
			point2 = { -4., 3. };
			point2 = { -2., -1. };
			triangle = { point1, point2, point3, "123456", "ff00ff" };
			VerifyTriangle(triangle, point1, point2, point3, "123456", "ff00ff");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetAera)
		BOOST_AUTO_TEST_CASE(return_rigth_value)
		{
			CPoint point1, point2, point3;
			CTriangle triangle(point1, point2, point3, "000000", "000000");
			VerifyDouble(triangle.GetArea(), 0.);

			point1 = { 1., -2. };
			point2 = { -3., 1. };
			point3 = { -1., -0.5 };
			triangle = { point1, point2, point3, "000000", "000000" };
			VerifyDouble(triangle.GetArea(), 0.);

			point1 = { 0., 0. };
			point2 = { 1., 2. };
			point3 = { 2., 1. };
			triangle = { point1, point2, point3, "000000", "000000" };
			VerifyDouble(triangle.GetArea(), 1.5);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetPerimeter)
		BOOST_AUTO_TEST_CASE(return_right_value)
		{
			CPoint point1, point2, point3;
			CTriangle triangle(point1, point2, point3, "000000", "000000");
			VerifyDouble(triangle.GetPerimeter(), 0.);

			point1 = { 1., -2. };
			point2 = { -3., 1. };
			point3 = { -1., -0.5 };
			triangle = { point1, point2, point3, "000000", "000000" };
			VerifyDouble(triangle.GetPerimeter(), 10.);

			point1 = { 0., 0. };
			point2 = { 1., 2. };
			point3 = { 2., 1. };
			triangle = { point1, point2, point3, "000000", "000000" };
			VerifyDouble(triangle.GetPerimeter(), sqrt(2) + 2. * sqrt(5));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(ToString)
		BOOST_AUTO_TEST_CASE(return_right_value)
		{
			CPoint point1 (0., 0.), point2 (1., 2.), point3 (2., 1.);
			CTriangle triangle = { point1, point2, point3, "123456", "ff00ff" };
			std::string expectedString = std::string("Triangle:\n")
				+ "\t1st point = (0.000, 0.000)\n"
				+ "\t2nd point = (1.000, 2.000)\n"
				+ "\t3rd point = (2.000, 1.000)\n"
				+ "\tfill color = #ff00ff\n"
				+ "\toutline color = #123456\n"
				+ "\tarea = 1.500\n"
				+ "\tperimeter = 5.886\n";
			BOOST_CHECK_EQUAL(triangle.ToString(), expectedString);
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

