#pragma once

#include "stdafx.h"
#include "2-CMyArray.h"
#include "2-CMyArrayIterator.h"

static const std::vector < std::string> STR_DATA = {
	"\"If\" Rudyard Kipling",
	"If you can keep your head when all about you",
	"Are losing theirs and blaming it on you,",
	"If you can trust yourself when all men doubt you,",
	"But make allowance for their doubting too;"
};

struct EmptyStringArray
{
	CMyArray <std::string> arr;
};
struct with_some_strings_ : EmptyStringArray
{
	with_some_strings_() {
		for (auto item : STR_DATA)
		{
			arr.Append(item);
		}
	}
};

BOOST_FIXTURE_TEST_SUITE(MyArrayIterator, with_some_strings_)
	BOOST_AUTO_TEST_SUITE(begin_iterator)
		BOOST_AUTO_TEST_CASE(give_access_to_firsts_element)
		{
			auto it = arr.begin();
			BOOST_CHECK_EQUAL(*it, STR_DATA[0]);
		}
		BOOST_AUTO_TEST_CASE(can_be_incremented)
		{
			auto it = arr.begin();
			BOOST_CHECK_EQUAL(*(++it), STR_DATA[1]);
			BOOST_CHECK_EQUAL(*(it++), STR_DATA[1]);
			BOOST_CHECK_EQUAL(*it, STR_DATA[2]);
		}
	BOOST_AUTO_TEST_SUITE_END()
/*
	BOOST_AUTO_TEST_SUITE(end_iterator)
		BOOST_AUTO_TEST_CASE(throw_if_try_get_access)
		{
			auto it = arr.end();
			BOOST_REQUIRE_THROW(*it, std::out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()
*/
	BOOST_AUTO_TEST_SUITE(rbegin_iterator)
		BOOST_AUTO_TEST_CASE(give_access_to_last_element)
		{
			auto it = arr.rbegin();
			BOOST_CHECK_EQUAL(*it, arr.GetBack());
		}
		BOOST_AUTO_TEST_CASE(can_be_incremented)
		{
			auto it = arr.rbegin();
			BOOST_CHECK_EQUAL(*(++it), STR_DATA[3]);
			BOOST_CHECK_EQUAL(*(it++), STR_DATA[3]);
			BOOST_CHECK_EQUAL(*it, STR_DATA[2]);
		}
	BOOST_AUTO_TEST_SUITE_END()
/*
	BOOST_AUTO_TEST_SUITE(rend_iterator)
		BOOST_AUTO_TEST_CASE(throw_if_try_get_access)
		{
			auto it = arr.rend();
			BOOST_REQUIRE_THROW(*it, std::out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()
*/
	BOOST_AUTO_TEST_CASE(can_be_compared)
	{
		auto it1 = arr.begin();
		auto it2 = arr.rbegin();
		++it1;
		++it2;
		BOOST_CHECK_EQUAL(it1 == it2, false);
		BOOST_CHECK_EQUAL(it1 != it2, true);
		++it1;
		BOOST_CHECK_EQUAL(it1 == it2, false);
		BOOST_CHECK_EQUAL(it1 != it2, true);
		++it2;
		BOOST_CHECK_EQUAL(it1 == it2, true);
		BOOST_CHECK_EQUAL(it1 != it2, false);
		++it1;
		BOOST_CHECK_EQUAL(it1 == it2, false);
		BOOST_CHECK_EQUAL(it1 != it2, true);
	}
	BOOST_AUTO_TEST_CASE(can_go_throught_array)
	{
		size_t i = 0;
		for (auto it = arr.begin(); it != arr.end(); ++it, ++i)
		{
			BOOST_CHECK_EQUAL(*it, STR_DATA[i]);
		}
		i = 0;
		for (auto item : arr)
		{
			BOOST_CHECK_EQUAL(item, STR_DATA[i]);
			++i;
		}
	}
	BOOST_AUTO_TEST_SUITE(can_be_dereferenced)
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

