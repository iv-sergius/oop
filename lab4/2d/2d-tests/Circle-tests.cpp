#include "stdafx.h"
#include "2d-tests.h"

BOOST_AUTO_TEST_SUITE(Circle)
	BOOST_AUTO_TEST_SUITE(constructor)
		BOOST_AUTO_TEST_CASE(create_right_object)
		{
			CPoint center;
			CCircle circle(center, 0., "000000", "000000");
			VerifyCircle(circle, { 0., 0. }, 0., "000000", "000000");

			center = { 1., -2. };
			circle = { center, 5., "123456", "ff00ff" };
			VerifyCircle(circle, { 1., -2. }, 5., "123456", "ff00ff");
		}
		BOOST_AUTO_TEST_SUITE(throw_exeption_on)
			BOOST_AUTO_TEST_CASE(negative_radus)
			{
				CPoint center;
				BOOST_REQUIRE_THROW(CCircle circle(center, -1., "000000", "000000"), std::invalid_argument);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetAera)
		BOOST_AUTO_TEST_CASE(return_rigth_value)
		{
			CPoint center(1., -2.);
			CCircle circle = { center, 5., "123456", "ff00ff" };
			VerifyDouble(circle.GetArea(), M_PI * 25.);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetPerimeter)
		BOOST_AUTO_TEST_CASE(return_right_value)
		{
			CPoint center(1., -2.);
			CCircle circle = { center, 5., "123456", "ff00ff" };
			VerifyDouble(circle.GetPerimeter(), M_PI * 10.);
		}
	BOOST_AUTO_TEST_SUITE_END()
/*
	BOOST_AUTO_TEST_SUITE(ToString)
		BOOST_AUTO_TEST_CASE(return_right_value)
		{
			CPoint center(1., -2.);
			CCircle circle = { center, 5., "123456", "ff00ff" };
			BOOST_CHECK_EQUAL(circle.ToString(), "Circle  1.000 -2.000  5.000  123456 ff00ff");
		}
	BOOST_AUTO_TEST_SUITE_END()
*/
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

