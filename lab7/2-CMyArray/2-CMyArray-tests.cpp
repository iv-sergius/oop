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

static const std::string DEFAULT_DATA;
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
	with_some_strings_(){
		for (auto item : STR_DATA)
		{
			arr.Append(item);
		}
	}
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

	struct with_some_elements_ : EmptyArray
	{
		with_some_elements_()
		{
			for (auto i = 0; i < 5; ++i)
			{
				arr.Append(i * i);
			}
		}
	};
	BOOST_FIXTURE_TEST_SUITE(When_array_non_empty, with_some_strings_)
		BOOST_AUTO_TEST_SUITE(after_copy_construction)
			BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
			{
				BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());
				auto copy(arr);
				BOOST_CHECK_EQUAL(copy.GetSize(), arr.GetSize());
				BOOST_CHECK_EQUAL(copy.GetCapacity(), arr.GetSize());
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(index_operator)
			BOOST_AUTO_TEST_CASE(get_access_to_element)
			{
				BOOST_CHECK_EQUAL(arr[0], STR_DATA[0]);
				BOOST_CHECK_EQUAL(arr[2], STR_DATA[2]);
				BOOST_CHECK_EQUAL(arr[4], STR_DATA[4]);
			}
			BOOST_AUTO_TEST_CASE(even_of_const_CMyArray)
			{
				const auto constArr(arr);
				BOOST_CHECK_EQUAL(constArr[0], STR_DATA[0]);
				BOOST_CHECK_EQUAL(constArr[2], STR_DATA[2]);
				BOOST_CHECK_EQUAL(constArr[4], STR_DATA[4]);
			}
			BOOST_AUTO_TEST_CASE(throw_on_invalid_index)
			{
				BOOST_REQUIRE_THROW(arr[6], std::out_of_range);
				BOOST_REQUIRE_THROW(arr[arr.GetSize()], std::out_of_range);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Resize_function)
			BOOST_AUTO_TEST_SUITE(when_increase_size_fill_new_elements_with_default_value)
				BOOST_AUTO_TEST_CASE(and_do_not_change_capacity_if_it_does_not_need)
				{
					size_t oldSize = arr.GetSize();
					size_t oldCapacity = arr.GetCapacity();
					BOOST_CHECK(oldCapacity - oldSize > 2);
					size_t newSize = oldCapacity - 1; // oldSize < newSize < oldCapacity
					arr.Resize(newSize);
					BOOST_CHECK_EQUAL(arr.GetSize(), newSize);
					BOOST_CHECK_EQUAL(arr.GetCapacity(), oldCapacity);
					// check data
					BOOST_CHECK_EQUAL(arr[oldSize - 1], STR_DATA[oldSize - 1]);
					BOOST_CHECK_EQUAL(arr[oldSize], DEFAULT_DATA);
					BOOST_CHECK_EQUAL(arr.GetBack(), DEFAULT_DATA);
				}
				BOOST_AUTO_TEST_CASE(and_can_increase_capacity)
				{
					size_t oldSize = arr.GetSize();
					size_t oldCapacity = arr.GetCapacity();
					size_t newSize = 2 * oldSize + 1; // oldSize < newSize < oldCapacity
					arr.Resize(newSize);
					BOOST_CHECK_EQUAL(arr.GetSize(), newSize);
					BOOST_CHECK_EQUAL(arr.GetCapacity(), newSize);
					BOOST_REQUIRE_NE(arr.GetCapacity(), oldCapacity);
					// check data
					BOOST_CHECK_EQUAL(arr[oldSize - 1], STR_DATA[oldSize - 1]);
					BOOST_CHECK_EQUAL(arr[oldSize], DEFAULT_DATA);
					BOOST_CHECK_EQUAL(arr.GetBack(), DEFAULT_DATA);
				}
			BOOST_AUTO_TEST_SUITE_END()
		
			BOOST_AUTO_TEST_CASE(do_not_corrupt_last_item)
			{
				size_t oldSize = arr.GetSize();
				size_t oldCapacity = arr.GetCapacity();
				arr.Resize(oldSize);
				BOOST_CHECK_EQUAL(arr.GetSize(), oldSize);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), oldCapacity);
				BOOST_CHECK_EQUAL(arr[oldSize - 1], STR_DATA[oldSize - 1]);
				arr.Resize(oldSize - 1);
				BOOST_CHECK_EQUAL(arr.GetSize(), oldSize - 1);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), oldCapacity);
				BOOST_CHECK_EQUAL(arr[oldSize - 2], STR_DATA[oldSize - 2]);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Clear_function)
			BOOST_AUTO_TEST_CASE(delete_all_elements)
			{
				size_t oldSize = arr.GetSize();
				BOOST_REQUIRE_NE(oldSize, 0);
				arr.Clear();
				BOOST_CHECK_EQUAL(arr.GetSize(), 0);
			}
			BOOST_AUTO_TEST_CASE(do_not_change_capacity)
			{
				size_t oldCapacity = arr.GetCapacity();
				arr.Clear();
				BOOST_CHECK_EQUAL(arr.GetCapacity(), oldCapacity);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Move_construcor)
			BOOST_AUTO_TEST_CASE(steal_previous_MyArray)
			{
				size_t wasSize = arr.GetSize();
				size_t wasCapacity = arr.GetCapacity();
				auto movedArr(move(arr));
				BOOST_CHECK_EQUAL(movedArr.GetSize(), wasSize);
				BOOST_CHECK_EQUAL(movedArr.GetCapacity(), wasCapacity);
				BOOST_CHECK_EQUAL(movedArr[0], STR_DATA[0]);
				BOOST_CHECK_EQUAL(movedArr.GetBack(), STR_DATA.back());
				BOOST_CHECK_EQUAL(arr.GetSize(), 0);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 0);
				//BOOST_REQUIRE_THROW(arr.GetBack(), std::out_of_range);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Move_Assignment)
			BOOST_AUTO_TEST_CASE(create_right_copy)
			{
				size_t wasSize = arr.GetSize();
				size_t wasCapacity = arr.GetCapacity();
				auto movedArr = std::move(arr);
				BOOST_CHECK_EQUAL(movedArr.GetSize(), wasSize);
				BOOST_CHECK_EQUAL(movedArr.GetCapacity(), wasCapacity);
				BOOST_CHECK_EQUAL(movedArr[0], STR_DATA[0]);
				BOOST_CHECK_EQUAL(movedArr.GetBack(), STR_DATA.back());
				BOOST_CHECK_EQUAL(arr.GetSize(), 0);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 0);
				//BOOST_REQUIRE_THROW(arr.GetBack(), std::out_of_range);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Copy_Assignment)
			BOOST_AUTO_TEST_CASE(create_right_copy)
			{
				size_t wasSize = arr.GetSize();
				size_t wasCapacity = arr.GetCapacity();
				auto movedArr = arr;
				BOOST_CHECK_EQUAL(movedArr.GetSize(), wasSize);
				BOOST_CHECK_EQUAL(movedArr.GetCapacity(), wasSize);
				BOOST_CHECK_EQUAL(movedArr[0], STR_DATA[0]);
				BOOST_CHECK_EQUAL(movedArr.GetBack(), STR_DATA.back());
				BOOST_CHECK_EQUAL(arr.GetSize(), wasSize);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), wasCapacity);
				BOOST_CHECK_EQUAL(arr[0], STR_DATA[0]);
				BOOST_CHECK_EQUAL(arr.GetBack(), STR_DATA.back());
		}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
