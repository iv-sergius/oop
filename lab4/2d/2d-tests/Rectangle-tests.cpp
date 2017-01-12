#include "stdafx.h"
#include "2d-tests.h"

BOOST_AUTO_TEST_SUITE(Rectangle)
	BOOST_AUTO_TEST_SUITE(constructor)
		BOOST_AUTO_TEST_CASE(create_right_object)
		{
			CPoint leftTop, rightBottom;
			CRectangle rectangle(leftTop, rightBottom, "000000", "000000");
			VerifyRectangle(rectangle, { 0., 0. }, { 0., 0. }, "000000", "000000");

			leftTop = { 1., -2. };
			rightBottom = { 5., 1. };
			rectangle = { leftTop, rightBottom, "123456", "ff00ff" };
			VerifyRectangle(rectangle, leftTop, rightBottom, "123456", "ff00ff");
		}
		BOOST_AUTO_TEST_SUITE(throw_exeption_if)
			BOOST_AUTO_TEST_CASE(rightBottom_is_not_right)
			{
				CPoint leftTop(1., -2.), rightBottom(0., 1.);
				BOOST_REQUIRE_THROW(CRectangle rectangle(leftTop, rightBottom, "123456", "ff00ff"), std::invalid_argument);
			}
			BOOST_AUTO_TEST_CASE(rightBottom_is_not_bottom)
			{
				CPoint leftTop(1., -2.), rightBottom(5., -3.);
				BOOST_REQUIRE_THROW(CRectangle rectangle(leftTop, rightBottom, "123456", "ff00ff"), std::invalid_argument);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetWidth)
		BOOST_AUTO_TEST_CASE(return_rigth_value)
		{
			CPoint leftTop(1., -2.), rightBottom(5., 1.);
			CRectangle rectangle(leftTop, rightBottom, "123456", "ff00ff");
			VerifyDouble(rectangle.GetWidth(), 4.);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetHeight)
		BOOST_AUTO_TEST_CASE(return_rigth_value)
		{
			CPoint leftTop(1., -2.), rightBottom(5., 1.);
			CRectangle rectangle(leftTop, rightBottom, "123456", "ff00ff");
			VerifyDouble(rectangle.GetHeight(), 3.);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetAera)
		BOOST_AUTO_TEST_CASE(return_rigth_value)
		{
			CPoint leftTop(1., -2.), rightBottom(5., 1.);
			CRectangle rectangle(leftTop, rightBottom, "123456", "ff00ff");
			VerifyDouble(rectangle.GetArea(), 12.);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(GetPerimeter)
		BOOST_AUTO_TEST_CASE(return_right_value)
		{
			CPoint leftTop(1., -2.), rightBottom(5., 1.);
			CRectangle rectangle(leftTop, rightBottom, "123456", "ff00ff");
			VerifyDouble(rectangle.GetPerimeter(), 14.);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(ToString)
		BOOST_AUTO_TEST_CASE(return_right_value)
		{
			CPoint leftTop(1., -2.), rightBottom(5., 1.);
			CRectangle rectangle(leftTop, rightBottom, "123456", "ff00ff");
			std::string expectedString = std::string("Rectangle:\n")
				+ "\tleft top point = (1.000, -2.000)\n"
				+ "\tright bottom point = (5.000, 1.000)\n"
				+ "\tfill color = #ff00ff\n"
				+ "\toutline color = #123456\n"
				+ "\tarea = 12.000\n"
				+ "\tperimeter = 14.000\n";
			BOOST_CHECK_EQUAL(rectangle.ToString(), expectedString);
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

