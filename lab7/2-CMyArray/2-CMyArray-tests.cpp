#include "stdafx.h"
#include "2-CMyArray.h"

using namespace std;

struct ArrayItem
{
	ArrayItem(int value = 0) : value(value)
	{}
	int value;
};

struct EmptyArray
{
	CMyArray<ArrayItem> arr;
};

BOOST_FIXTURE_TEST_SUITE(MyArray, EmptyArray)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(arr.GetSize(), 0u);
		}
		BOOST_AUTO_TEST_CASE(has_0_capacity)
		{
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_appending_an_item)
		BOOST_AUTO_TEST_CASE(increases_its_size_and_capacity)
		{
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 1u);
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 2u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 2u);
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 3u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
			arr.Append(ArrayItem());
			BOOST_CHECK_EQUAL(arr.GetSize(), 4u);
			BOOST_CHECK_EQUAL(arr.GetCapacity(), 4u);
		}
		BOOST_AUTO_TEST_CASE(it_becomes_available_at_the_back)
		{
			arr.Append(1);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 1);
			arr.Append(2);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 2);
			arr.Append(3);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 3);
			arr.Append(4);
			BOOST_CHECK_EQUAL(arr.GetBack().value, 4);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(after_copy_construction)
		BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
		{
			for (auto i = 0; i < 6; ++i)
			{
				arr.Append(i);
			}
			BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());

			auto copy(arr);
			BOOST_CHECK_EQUAL(copy.GetSize(), arr.GetSize());
			BOOST_CHECK_EQUAL(copy.GetCapacity(), arr.GetSize());
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct with_some_elements_ : EmptyArray
	{
		with_some_elements_()
		{
			for (auto i = 0; i < 6; ++i)
			{
				arr.Append(i * i);
			}
		}
	};
	BOOST_FIXTURE_TEST_SUITE(When_array_non_empty, with_some_elements_)
		BOOST_AUTO_TEST_SUITE(index_operator)
			BOOST_AUTO_TEST_CASE(get_access_to_element)
			{
				BOOST_CHECK_EQUAL(arr[0].value, 0);
				BOOST_CHECK_EQUAL(arr[3].value, 9);
				BOOST_CHECK_EQUAL(arr[5].value, 25);
			}
			BOOST_AUTO_TEST_CASE(throw_on_invalid_index)
			{
				BOOST_REQUIRE_THROW(arr[6], std::out_of_range);
				BOOST_REQUIRE_THROW(arr[arr.GetSize()], std::out_of_range);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Resize_function)
			BOOST_AUTO_TEST_CASE(new_elements_have_default_value)
			{
				size_t oldSize = arr.GetSize();
				arr.Resize(oldSize + 2);
				BOOST_CHECK_EQUAL(arr.GetSize(), oldSize + 2);
				BOOST_CHECK_EQUAL(arr[oldSize].value, ArrayItem().value);
				BOOST_CHECK_EQUAL(arr[oldSize + 1].value, ArrayItem().value);
				size_t newSize = 2 * oldSize + 1;
				arr.Resize(newSize);
				BOOST_CHECK_EQUAL(arr.GetSize(), newSize);
				BOOST_CHECK_EQUAL(arr[newSize - 1].value, ArrayItem().value);
			}
			BOOST_AUTO_TEST_CASE(do_not_corrupt_last_item)
			{
				size_t oldSize = arr.GetSize();
				arr.Resize(oldSize);
				BOOST_CHECK_EQUAL(arr.GetSize(), oldSize);
				BOOST_CHECK_EQUAL(arr[oldSize -1].value, arr[oldSize - 1].value);
				arr.Resize(oldSize - 1);
				BOOST_CHECK_EQUAL(arr.GetSize(), oldSize - 1);
				BOOST_CHECK_EQUAL(arr[oldSize - 2].value, arr[oldSize - 2].value);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
