#include "stdafx.h"
#include "2d-tests.h"

BOOST_AUTO_TEST_SUITE(NormalizeColor_function)
	BOOST_AUTO_TEST_CASE(do_not_change_already_normal_color)
	{
		std::string color = "123456";
		BOOST_CHECK_EQUAL(NormalizeColor(color), color);
		color = "abcdef";
		BOOST_CHECK_EQUAL(NormalizeColor(color), color);
	}
	BOOST_AUTO_TEST_CASE(convert_to_lowercase)
	{
		std::string color = "AbCdeF";
		BOOST_CHECK_EQUAL(NormalizeColor(color), "abcdef");
	}
	BOOST_AUTO_TEST_SUITE(throw_exeption_on)
		BOOST_AUTO_TEST_CASE(incorrect_symbols_in_color_strings)
		{
			BOOST_REQUIRE_THROW(NormalizeColor("#EEEEE"), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(incorrect_length_of_color_string)
		{
			BOOST_REQUIRE_THROW(NormalizeColor("12345"), std::invalid_argument);
			BOOST_REQUIRE_THROW(NormalizeColor("1234567"), std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()