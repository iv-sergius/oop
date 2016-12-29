#include "stdafx.h"
#include <boost\test\unit_test.hpp>
#include "../1-solve4.h"

void CheckSolve2(EquationRoot2 solution, const std::vector<double> &coef)
{
	for (size_t i = 0; i < solution.numRoots; ++i)
	{
		double x = solution.roots[i];
		BOOST_CHECK_EQUAL(coef.size(), 3);
		if (abs(x) > 1)
		{
			BOOST_CHECK_SMALL(abs((coef[0] * x + coef[1]) * x + coef[2]), 3. * abs(x) * DBL_EPSILON );
		}
		else
		{
			BOOST_CHECK_SMALL(abs((coef[0] * x + coef[1]) * x + coef[2]), 3. * DBL_EPSILON);
		}
	}
}

BOOST_AUTO_TEST_SUITE(Solve_2_degree)
	BOOST_AUTO_TEST_CASE(must_throw_if_degree_is_not_2)
	{
		BOOST_REQUIRE_THROW(Solve2(0., 1., 1.), std::invalid_argument);
	}
	BOOST_AUTO_TEST_SUITE(return_a)
		BOOST_AUTO_TEST_CASE(empty_solution_if_discriminant_is_negative)
		{
			EquationRoot2 answer;
			std::vector<double> coef = {1, 0, 1};
			answer = Solve2(coef[0], coef[1], coef[2]);
			BOOST_CHECK_EQUAL(answer.numRoots, 0);
			coef ={ -10, 7, -5 };
			answer = Solve2(coef[0], coef[1], coef[2]);
			BOOST_CHECK_EQUAL(answer.numRoots, 0);
		}
		BOOST_AUTO_TEST_CASE(empty_solution_if_discriminant_equal_0)
		{
			EquationRoot2 answer;
			std::vector<double> coef = { 1, 2, 1 };
			answer = Solve2(coef[0], coef[1], coef[2]);
			BOOST_CHECK_EQUAL(answer.numRoots, 1);
			CheckSolve2(answer, coef);
			coef = { -4, 4, -1 };
			answer = Solve2(coef[0], coef[1], coef[2]);
			BOOST_CHECK_EQUAL(answer.numRoots, 1);
			CheckSolve2(answer, coef);
		}
		BOOST_AUTO_TEST_CASE(empty_solution_if_discriminant_is_positive)
		{
			EquationRoot2 answer;
			std::vector<double> coef = { 1, 5, 1 };
			answer = Solve2(coef[0], coef[1], coef[2]);
			BOOST_CHECK_EQUAL(answer.numRoots, 2);
			CheckSolve2(answer, coef);
			coef = { -12, -7, -1 };
			answer = Solve2(coef[0], coef[1], coef[2]);
			BOOST_CHECK_EQUAL(answer.numRoots, 2);
			CheckSolve2(answer, coef);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

void CheckRoot3(double root, const std::vector<double> &coef)
{
}

BOOST_AUTO_TEST_SUITE(Root_3_degree)
	BOOST_AUTO_TEST_CASE(must_throw_if_degree_is_not_3)
	{
		BOOST_REQUIRE_THROW(Root3(0., 1., 1., 1.), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(return_correct_values)
	{
		double root = Root3(1., 0., 4., -5.);
		BOOST_CHECK_EQUAL(root, 1);
		root = Root3(1., 0., 1., -10.);
		BOOST_CHECK_EQUAL(root, 2);
		root = Root3(1., 0., -5., 2.);
		BOOST_CHECK_EQUAL(root, 2);
		root = Root3(-4., 3., -2., -9.);
		BOOST_CHECK_EQUAL(root, -1.);
	}
BOOST_AUTO_TEST_SUITE_END()


void CheckSolve4(EquationRoot4 solution, const std::vector<double> &coef)
{
	for (size_t i = 0; i < solution.numRoots; ++i)
	{
		double x = solution.roots[i];
		BOOST_CHECK_EQUAL(coef.size(), 5);
		if (abs(x) > 1)
		{
			BOOST_CHECK_SMALL(abs((((coef[0] * x + coef[1]) * x + coef[2]) * x + coef[3]) + coef[4]), 5. * abs(x) * DBL_EPSILON);
		}
		else
		{
			BOOST_CHECK_SMALL(abs((((coef[0] * x + coef[1]) * x + coef[2]) * x + coef[3]) + coef[4]), 5. * DBL_EPSILON);
		}
	}
}
BOOST_AUTO_TEST_SUITE(Solve_4_degree)
	BOOST_AUTO_TEST_CASE(must_throw_if_degree_is_not_4)
	{
		BOOST_REQUIRE_THROW(Solve4(0., 1., 1., 1., 1.), std::invalid_argument);
	}
	BOOST_AUTO_TEST_SUITE(return_a)
		BOOST_AUTO_TEST_CASE(empty_solution)
		{
			EquationRoot4 answer;
			std::vector<double> coef = {1, 0, 0, 0 ,1};
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 0);
			coef ={ -10, 7, -5, 0, -1};
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 0);
		}
		BOOST_AUTO_TEST_CASE(solution_with_1_root)
		{
			EquationRoot4 answer;
			std::vector<double> coef = { 1, 0, 0, 0 ,1 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
	//	BOOST_CHECK_EQUAL(answer.numRoots, 1);
			CheckSolve4(answer, coef);
			coef = { -10, 7, -5, 0, -1 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 0);
//			BOOST_CHECK_EQUAL(answer.numRoots, 1);
			CheckSolve4(answer, coef);
		}
		BOOST_AUTO_TEST_CASE(solution_with_2_roots)
		{
		}
		BOOST_AUTO_TEST_CASE(solution_with_3_roots)
		{
		}
		BOOST_AUTO_TEST_CASE(solution_with_4_roots)
		{
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
