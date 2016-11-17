// 4-generate-prime-tests.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <boost\test\unit_test.hpp>
#include "..\4-generate-prime.h"

BOOST_AUTO_TEST_SUITE(Test_GeneratePrimeNumbersSet_function)

	BOOST_AUTO_TEST_SUITE(Test_limint_values_of_upperBound_parameter)

		BOOST_AUTO_TEST_CASE(must_return_empty_set_on_zero_upperBound)
		{
			std::set<size_t>  mustBeEmptySet = GeneratePrimeNumbersSet(0);
			BOOST_CHECK(mustBeEmptySet.empty());
		}

		BOOST_AUTO_TEST_CASE(must_return_empty_set_on_upperBound_equal_1)
		{
			std::set<size_t>  mustBeEmptySet = GeneratePrimeNumbersSet(1);
			BOOST_CHECK(mustBeEmptySet.empty());
		}

		BOOST_AUTO_TEST_CASE(must_return_empty_set_on_upperBound_equal_1000000001)
		{
			std::set<size_t>  mustBeEmptySet = GeneratePrimeNumbersSet(MAX_UPPER_BOUND + 1);
			BOOST_CHECK(mustBeEmptySet.empty());
		}

		BOOST_AUTO_TEST_SUITE_END()
		
		std::set<size_t>  resultSet;
		BOOST_AUTO_TEST_SUITE(Test_for_digit_upperBound_parametr)
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_2_must_be_only_2)
			{
				resultSet.insert(2);
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(2));
			}
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_3_must_be__2_and_3)
			{
				resultSet.insert(3);
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(3));
			}
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_4_must_be__2_and_3)
			{
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(4));
			}
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_5_must_be__2_3_5)
			{
				resultSet.insert(5);
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(5));
			}
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_6_must_be__2_3_5)
			{
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(6));
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(Test_for_two_digit_upperBound_parametr)
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_10_must_be__2_3_5_7)
			{
				resultSet.insert(7);
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(10));
			}
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_20_must_be__2_3_5_7_11_13_17_19)
			{
				resultSet.insert(11);
				resultSet.insert(13);
				resultSet.insert(17);
				resultSet.insert(19);
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(20));
			}
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_28_must_be__2_3_5_7_11_13_17_19_23)
			{
				resultSet.insert(23);
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(28));
			}
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_29_must_be__2_3_5_7_11_13_17_19_23_29)
			{
				resultSet.insert(29);
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(29));
			}
			BOOST_AUTO_TEST_CASE(Primes_less_or_equal_30_must_be__2_3_5_7_11_13_17_19_23_29)
			{
				BOOST_CHECK(resultSet == GeneratePrimeNumbersSet(30));
			}
		BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

