#include "stdafx.h"
#include "2-CMyArray.h"

using namespace std;

static const int THROW_CONSTRUCTOR = -1;
static const int THROW_COPY_CONSTRUCTOR = -2;
static const int THROW_MOVE = -3;
static const size_t LENGTH_DATA = 5;

struct ArrayItem
{
	ArrayItem(int val = 0)
	{
		value = val;
		m_isDestuct = false;
		if (value == THROW_CONSTRUCTOR)
		{
			throw std::exception("Constructor exeption only for test");
		}
	};
	ArrayItem(const ArrayItem & rhs)
	{
		value = rhs.value;
		m_isDestuct = rhs.m_isDestuct;
		if (value == THROW_COPY_CONSTRUCTOR)
		{
			throw std::exception("Copy exeption only for test");
		}
	};
	ArrayItem& operator = (ArrayItem &&rhs)
	{
		value = rhs.value;
		m_isDestuct = rhs.m_isDestuct;
		if (value == THROW_MOVE)
		{
			throw std::exception("Move exeption only for test");
		}
		return *this;
	}
	int value;
	~ArrayItem()
	{
		if (m_isDestuct)
		{
			assert(!m_isDestuct);
		}
		m_isDestuct = true;
	}
private:
	bool m_isDestuct = false;
};

struct EmptyArray
{
	CMyArray<ArrayItem> arr;
};

struct with_some_elements_ : EmptyArray
{
	with_some_elements_()
	{
		for (auto i = 0; i < LENGTH_DATA; ++i)
		{
			arr.Append(i);
		}
/*
		for (auto i = 0; i <= LENGTH_DATA; ++i)
		{
			arrWithThrowsOnCopy.Append(THROW_COPY_CONSTRUCTOR);
		}
		for (auto i = 0; i <= LENGTH_DATA; ++i)
		{
			//arrWithThrowsOnMove.Append(THROW_MOVE);
		}
*/
	}
};

void VerifyItem(const ArrayItem & item, const ArrayItem & expectedItem)
{
	BOOST_CHECK_EQUAL(item.value, expectedItem.value);
}

void VerifyMyArrayEquality(const CMyArray<ArrayItem> & arr)
{
	for (size_t i = 0; i < LENGTH_DATA; ++i)
	{
		BOOST_CHECK_EQUAL(arr[i].value, i);
	}
}

void VerifyMyArrayEquality(const CMyArray<ArrayItem> & arr, const CMyArray<ArrayItem> & expectedArr)
{
	BOOST_CHECK_EQUAL(arr.GetSize(), expectedArr.GetSize());
	for (size_t i = 0; i < arr.GetSize(); ++i)
	{
		BOOST_CHECK_EQUAL(arr[i].value, expectedArr[i].value);
	}
}


BOOST_AUTO_TEST_SUITE(Array_Item)
	BOOST_AUTO_TEST_CASE(have_defaut_constructor)
	{
		ArrayItem item(0);
		VerifyItem(item, ArrayItem());
	}
	BOOST_AUTO_TEST_CASE(can_throw_exeption_in_constructor)
	{
		BOOST_REQUIRE_THROW(ArrayItem item(THROW_CONSTRUCTOR), std::exception);
	}
	BOOST_AUTO_TEST_CASE(can_throw_exeption_in_copy_constructor)
	{
		ArrayItem item(THROW_COPY_CONSTRUCTOR);
		BOOST_REQUIRE_THROW(ArrayItem copy(item), std::exception);
	}
	BOOST_AUTO_TEST_CASE(can_throw_exeption_on_move)
	{
		ArrayItem item(THROW_MOVE), move;
		BOOST_REQUIRE_THROW(move = std::move(item), std::exception);
	}
	/*BOOST_AUTO_TEST_CASE(can_throw_exeption_in_second_destructor)
	{
		ArrayItem item(0);
		item.~ArrayItem();
		BOOST_REQUIRE_THROW(item.~ArrayItem(), std::exception);
	}*/
BOOST_AUTO_TEST_SUITE_END()


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
		BOOST_AUTO_TEST_SUITE(array_do_not_change_if_rise_exception)
			BOOST_AUTO_TEST_CASE(in_constructor)
			{
				arr.Append(1);
				BOOST_CHECK_EQUAL(arr.GetSize(), 1);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 1);
				BOOST_REQUIRE_THROW(arr.Append(THROW_CONSTRUCTOR), std::exception);
				VerifyItem(arr.GetBack(), ArrayItem(1));
				BOOST_CHECK_EQUAL(arr.GetSize(), 1);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 1);
			}
			BOOST_AUTO_TEST_CASE(while_copy)
			{
				arr.Append(1);
				BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 1u);
				ArrayItem nonMoveItem(THROW_COPY_CONSTRUCTOR);
				BOOST_REQUIRE_THROW(arr.Append(nonMoveItem), std::exception);
				VerifyItem(arr.GetBack(), ArrayItem(1));
				BOOST_CHECK_EQUAL(arr.GetSize(), 1u);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 1u); 
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(When_array_non_empty, with_some_elements_)
		BOOST_AUTO_TEST_SUITE(after_copy_construction)
			BOOST_AUTO_TEST_CASE(has_size_capacity_equal_to_size_of_original_array)
			{
				BOOST_CHECK_NE(arr.GetSize(), arr.GetCapacity());
				auto copy(arr);
				BOOST_CHECK_EQUAL(copy.GetSize(), arr.GetSize());
				BOOST_CHECK_EQUAL(copy.GetCapacity(), arr.GetSize());
				VerifyMyArrayEquality(copy, arr);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(index_operator)
			BOOST_AUTO_TEST_CASE(get_access_to_element)
			{
				VerifyItem(arr[0], ArrayItem(0));
				VerifyItem(arr[2], ArrayItem(2));
				VerifyItem(arr[4], ArrayItem(4));
			}
			BOOST_AUTO_TEST_CASE(even_of_const_CMyArray)
			{
				const auto constArr(arr);
				VerifyItem(constArr[0], ArrayItem(0));
				VerifyItem(constArr[2], ArrayItem(2));
				VerifyItem(constArr[4], ArrayItem(4));
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
					VerifyItem(arr[oldSize - 1], ArrayItem(oldSize - 1));
					VerifyItem(arr[oldSize], ArrayItem());
					VerifyItem(arr.GetBack(), ArrayItem());
				}
				BOOST_AUTO_TEST_CASE(and_can_increase_capacity)
				{
					size_t oldSize = arr.GetSize();
					size_t oldCapacity = arr.GetCapacity();
					size_t newSize = 2 * oldSize + 1; // must be reallocate
					arr.Resize(newSize);
					BOOST_CHECK_EQUAL(arr.GetSize(), newSize);
					BOOST_CHECK_EQUAL(arr.GetCapacity(), newSize);
					BOOST_REQUIRE_NE(arr.GetCapacity(), oldCapacity);
					// check data
					VerifyItem(arr[oldSize - 1], ArrayItem(oldSize - 1));
					VerifyItem(arr[oldSize], ArrayItem());
					VerifyItem(arr.GetBack(), ArrayItem());
				}
			BOOST_AUTO_TEST_SUITE_END()
		
			BOOST_AUTO_TEST_CASE(do_not_corrupt_data_if_throw_in_reallocation)
			{
				auto arrWithThrowsOnCopy(arr);
				arrWithThrowsOnCopy[2].value = THROW_COPY_CONSTRUCTOR; // inject noncopy array item
				size_t oldSize = arrWithThrowsOnCopy.GetSize();
				size_t oldCapacity = arrWithThrowsOnCopy.GetCapacity();
				size_t newSize = 2 * oldSize + 1; // must be reallocate
				BOOST_REQUIRE_THROW(arrWithThrowsOnCopy.Resize(newSize), std::exception);
				BOOST_CHECK_EQUAL(arrWithThrowsOnCopy.GetSize(), oldSize);
				BOOST_CHECK_EQUAL(arrWithThrowsOnCopy.GetCapacity(), oldSize);
				// check data
				VerifyItem(arr.GetBack(), ArrayItem(4));
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
				VerifyItem(movedArr[0], ArrayItem());
				VerifyItem(movedArr.GetBack(), ArrayItem(4));
				BOOST_CHECK_EQUAL(arr.GetSize(), 0);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), 0);
			}
/*
			BOOST_AUTO_TEST_CASE(do_not_change_anything_on_throw)
			{
				size_t wasSize = arrWithThrowsOnMove.GetSize();
				size_t wasCapacity = arrWithThrowsOnMove.GetCapacity();
				CMyArray<ArrayItem> movedArr;
				BOOST_REQUIRE_THROW(movedArr = std::move(arrWithThrowsOnMove), std::exception);
			}
*/
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Move_Assignment)
			BOOST_AUTO_TEST_CASE(create_right_copy)
			{
				size_t wasSize = arr.GetSize();
				size_t wasCapacity = arr.GetCapacity();
				auto movedArr = std::move(arr);
				BOOST_CHECK_EQUAL(movedArr.GetSize(), wasSize);
				BOOST_CHECK_EQUAL(movedArr.GetCapacity(), wasCapacity);
				VerifyItem(movedArr[0], ArrayItem(0));
				VerifyItem(movedArr.GetBack(), ArrayItem(4));
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
				VerifyItem(movedArr[0], ArrayItem(0));
				VerifyItem(movedArr.GetBack(), ArrayItem(4));
				BOOST_CHECK_EQUAL(arr.GetSize(), wasSize);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), wasCapacity);
				VerifyMyArrayEquality(movedArr, arr);
			}
			BOOST_AUTO_TEST_CASE(do_not_change_anything_on_throw)
			{
				auto arrWithThrowsOnCopy(arr);
				arrWithThrowsOnCopy[0].value = THROW_COPY_CONSTRUCTOR; // inject noncopy array item
				arrWithThrowsOnCopy[3].value = THROW_COPY_CONSTRUCTOR; // inject noncopy array item
				arrWithThrowsOnCopy.Resize(4);
				size_t wasSize = arr.GetSize();
				size_t wasCapacity = arr.GetCapacity();
				size_t wasArrWithThrowSize = arrWithThrowsOnCopy.GetSize();
				size_t wasArrWithThrowCapacity = arrWithThrowsOnCopy.GetCapacity();
				BOOST_REQUIRE_NE(wasSize, wasArrWithThrowSize);
				BOOST_REQUIRE_THROW(arr = arrWithThrowsOnCopy, std::exception);
				
				BOOST_CHECK_EQUAL(arrWithThrowsOnCopy.GetSize(), wasArrWithThrowSize);
				BOOST_CHECK_EQUAL(arrWithThrowsOnCopy.GetCapacity(), wasArrWithThrowCapacity);
				VerifyItem(arrWithThrowsOnCopy[0], ArrayItem(THROW_COPY_CONSTRUCTOR));
				VerifyItem(arrWithThrowsOnCopy.GetBack(), ArrayItem(THROW_COPY_CONSTRUCTOR));
				
				BOOST_CHECK_EQUAL(arr.GetSize(), wasSize);
				BOOST_CHECK_EQUAL(arr.GetCapacity(), wasCapacity);
				VerifyItem(arr[0], ArrayItem(0));
				VerifyItem(arr.GetBack(), ArrayItem(4));
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
