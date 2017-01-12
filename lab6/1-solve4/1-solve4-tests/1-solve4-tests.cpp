#include "stdafx.h"
#include <boost\test\unit_test.hpp>
#include "../1-solve4.h"

static const double R_EPS = 1e-12;

void VerifyRoot(const double root, const double functionValue)
{
	BOOST_CHECK_SMALL(functionValue, R_EPS);
}

void CheckSolve2(EquationRoot2 solution, const std::vector<double> &coef)
{
	for (size_t i = 0; i < solution.numRoots; ++i)
	{
		double x = solution.roots[i];
		BOOST_CHECK_EQUAL(coef.size(), 3);
		double y = (coef[0] * x + coef[1]) * x + coef[2];
		VerifyRoot(x, y);
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
		BOOST_AUTO_TEST_CASE(one_solution_if_discriminant_equal_0)
		{
			EquationRoot2 answer;
			std::vector<double> coef = { 1, 0, 0 };
			answer = Solve2(coef[0], coef[1], coef[2]);
			BOOST_CHECK_EQUAL(answer.numRoots, 1);
			CheckSolve2(answer, coef);
			coef = { -4, 4, -1 };
			answer = Solve2(coef[0], coef[1], coef[2]);
			BOOST_CHECK_EQUAL(answer.numRoots, 1);
			CheckSolve2(answer, coef);
		}
		BOOST_AUTO_TEST_CASE(two_solution_if_discriminant_is_positive)
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
	double y = ((coef[0] * root + coef[1]) * root + coef[2]) * root + coef[3];
	VerifyRoot(root, y);
}

BOOST_AUTO_TEST_SUITE(Root_3_degree)
	BOOST_AUTO_TEST_CASE(must_throw_if_degree_is_not_3)
	{
		BOOST_REQUIRE_THROW(Root3(0., 1., 1., 1.), std::invalid_argument);
	}
	BOOST_AUTO_TEST_CASE(return_correct_values)
	{
		double root = Root3(1., 0., 0., 0.);
		BOOST_CHECK_EQUAL(root, 0.);
		root = Root3(1., 0., 4., -5.);
		BOOST_CHECK_EQUAL(root, 1);
		root = Root3(1., 0., 1., -10.);
		BOOST_CHECK_EQUAL(root, 2);
		root = Root3(1., 0., -5., 2.);
		BOOST_CHECK_EQUAL(root, 2);
		root = Root3(1., 1., -4., -4.);
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
		double y = (((coef[0] * x + coef[1]) * x + coef[2]) * x + coef[3]) * x + coef[4];
		VerifyRoot(x, y);
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
			std::vector<double> coef = {1, 0, 0, 0, 1};
			BOOST_REQUIRE_THROW(Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]), std::domain_error);
			coef ={ -10, 7, -5, 0, -1};
			BOOST_REQUIRE_THROW(Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]), std::domain_error);
	}
		BOOST_AUTO_TEST_CASE(solution_with_1_root)
		{
			EquationRoot4 answer;
			std::vector<double> coef = { 1, 0, 0, 0, 0 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 1);
			CheckSolve4(answer, coef);
			BOOST_CHECK_EQUAL(answer.roots[0], 0.);

			coef = { 16, -32, 24, -8, 1 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 1);
			CheckSolve4(answer, coef);
			BOOST_CHECK_EQUAL(answer.roots[0], 0.5);
		}
		BOOST_AUTO_TEST_CASE(solution_with_2_roots)
		{
			EquationRoot4 answer;
			std::vector<double> coef = { 1, 0, -2, 0, 1 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 2);
			CheckSolve4(answer, coef);
			
			coef = { 1, 1, 0, 0, 0 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 2);
			CheckSolve4(answer, coef);
			
			coef = { 4, -12, 13, -6, 1 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 2);
			CheckSolve4(answer, coef);
		}
		BOOST_AUTO_TEST_CASE(solution_with_3_roots)
		{
			EquationRoot4 answer;
			std::vector<double> coef = { 2, -3, 1, 0, 0 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 3);
			CheckSolve4(answer, coef);
			
			coef = { 2, -9, 14, -9, 2 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 3);
			CheckSolve4(answer, coef);
			
		}
		BOOST_AUTO_TEST_CASE(solution_with_4_roots)
		{
			EquationRoot4 answer;
			std::vector<double> coef = { 1, -2, -1, 2, 0 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 4);
			CheckSolve4(answer, coef);
			
			coef = { 4, -12, 7, 3, -2 };
			answer = Solve4(coef[0], coef[1], coef[2], coef[3], coef[4]);
			BOOST_CHECK_EQUAL(answer.numRoots, 4);
			CheckSolve4(answer, coef);
			
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

