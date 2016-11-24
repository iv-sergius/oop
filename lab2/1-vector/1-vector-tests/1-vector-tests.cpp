// 1-vector-tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost\test\unit_test.hpp>
#include "..\1-vector.h"



BOOST_AUTO_TEST_SUITE(Test_vector_input_output)

	BOOST_AUTO_TEST_SUITE(Read_to_vector_from_stream)
		BOOST_AUTO_TEST_CASE(get_empty_vector_from_empty_stream)
		{
			std::stringstream strInStream(" ");
			BOOST_CHECK(ReadVectorFromStream(strInStream).empty());
		}
		BOOST_AUTO_TEST_CASE(from_non_empty_stream)
		{
			std::stringstream strInStream("0 -1 2.5 4.999 -4.9999");
			const std::vector<double> correctVector = { 0, -1, 2.5, 4.999, -4.9999 };
			BOOST_CHECK(correctVector == ReadVectorFromStream(strInStream));
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(Write_to_stream_from_vector)
		BOOST_AUTO_TEST_CASE(get_empty_stream_from_empty_vector)
		{
			std::stringstream strOutStream;
			const std::vector<double> emptyVector;
			WriteVectorToStream(emptyVector, strOutStream);
			BOOST_CHECK(strOutStream.str() == "\n");
		}
		BOOST_AUTO_TEST_CASE(from_non_empty_vector)
		{
			std::stringstream strOutStream;
			const std::vector<double> sourceVector = { 0, -1, 2.5, 4.999, -4.9999 };
			WriteVectorToStream(sourceVector, strOutStream);
			BOOST_CHECK(strOutStream.str() == "0.000 -1.000 2.500 4.999 -5.000 \n");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_vector_transformation)
		BOOST_AUTO_TEST_CASE(Do_not_transform_empty_vector)
		{
			std::vector<double> emptyVector;
			TransformVector(emptyVector);
			BOOST_CHECK(emptyVector.empty());
		}
		BOOST_AUTO_TEST_CASE(Vector_with_1_element)
		{
			std::vector<double> sourceVector = {-1};
			TransformVector(sourceVector);
			const std::vector<double> resultVector = {-2};
			BOOST_CHECK(sourceVector == resultVector);
		}
		BOOST_AUTO_TEST_CASE(Vector_with_few_element)
		{
			std::vector<double> sourceVector = { -3, 2, -1, 1 }; //3.22
			TransformVector(sourceVector);
			const std::vector<double> resultVector = { -6, -1, -2, -2 };
			BOOST_CHECK(sourceVector == resultVector);
		}
	BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()

