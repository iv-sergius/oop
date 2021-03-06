#include "stdafx.h"
#include "1-solve4.h"
#include <float.h>
#include <assert.h>

EquationRoot2 Solve2(double a, double b, double c)
{
	if (abs(a) < DBL_EPSILON)
	{
		throw std::invalid_argument("Degree must be equal 2\n");
	}
	EquationRoot2 solution;
	double D = b * b - 4. * a * c;
	if (abs(D) < 100. * DBL_EPSILON) // 1 root
	{
		solution.numRoots = 1;
		solution.roots[0] = -b / a / 2.;
		return solution;
	} 
	else if (D < 0.) // no any roots
	{
		solution.numRoots = 0;
		return solution;
	}
	else
	{
		solution.numRoots = 2;
		if (b >= 0)
		{
			solution.roots[0] = (- b - sqrt(D)) / a / 2.;
		}
		else
		{
			solution.roots[0] = (- b + sqrt(D)) / a / 2.;
		}
		if (abs(c) < DBL_EPSILON)
		{
			solution.roots[1] = -b / a - solution.roots[0];
		}
		else
		{
			solution.roots[1] = c / a / solution.roots[0];
		}
		return solution;
	}
}

void AddRootsToEquation(EquationRoot4 &solution4, const EquationRoot2 &solution2)
{
	size_t numRoots = solution4.numRoots;
	for (size_t i = 0; i < solution2.numRoots; ++i)
	{
		bool isNewRoot = true;
		for (size_t j = 0; (j < numRoots) && isNewRoot; ++j)
		{
			isNewRoot = abs(solution4.roots[j] - solution2.roots[i]) > DBL_EPSILON;
		}
		if (isNewRoot)
		{
			solution4.roots[numRoots] = solution2.roots[i];
			++numRoots;
		}
	}
	solution4.numRoots = numRoots;
}

EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
	if (abs(a) < DBL_EPSILON)
	{
		throw std::invalid_argument("Degree must be equal 4\n");
	}
	EquationRoot4 answer;
	answer.numRoots = 0;
	// normalize
	double A = b / a;
	double B = c / a;
	double C = d / a;
	double D = e / a;

	double y0, alpha, beta;
	y0 = Root3(1., -B, A * C - 4. * D, 4. * B * D - A * A * D - C * C);
	alpha = sqrt(A * A / 4. - B + y0);
	if (abs(alpha) < DBL_EPSILON) // if alpha = 0
	{
		beta = sqrt(y0 * y0 / 4. - D);
	}
	else
	{
		beta = ((A / 2) * y0 - C) / alpha/ 2.;
	}
	assert(	abs(beta) - sqrt(y0 * y0 / 4. - D) < 2 * std::max(1., abs(y0)) * DBL_EPSILON );
	
	if (abs(alpha) + abs(beta) < 2. * DBL_EPSILON)
	{
		EquationRoot2 subSolution;
		subSolution = Solve2(1., A / 2., y0 / 2.);
		AddRootsToEquation(answer, subSolution);
	}
	else
	{
		EquationRoot2 subSolution;
		subSolution = Solve2(1., A / 2. + alpha, y0 / 2. + beta);
		AddRootsToEquation(answer, subSolution);
		subSolution = Solve2(1., A / 2. - alpha, y0 / 2. - beta);
		AddRootsToEquation(answer, subSolution);
	}
	if (answer.numRoots == 0)
	{
		throw(std::domain_error("No any root"));
	}
	return answer;
}

// find one of roots of 3rd derge equations
double Root3(double a, double b, double c, double d)
{
	if (abs(a) < DBL_EPSILON)
	{
		throw std::invalid_argument("Degree must be equal 3\n");
	}

	b /= a;
	c /= a;
	d /= a;
	a = 1.;

	double p = c - b * b / 3.;
	double q = d + b * b * b * 2. / 27 - b * c / 3.;

	double Q = q * q / 4. + p * p * p / 27.;
	//double Q = pow(q / 2., 2) + pow(p / 3., 3);
	double y, z;
	if (abs(q) + abs(p) < 2. * DBL_EPSILON) // Q == 0 
	//if (abs(Q) < DBL_EPSILON)
	{
		y = 0.;
	}
	else if (Q > 0.)
	{
		z = (q < 0) ? pow(- q / 2. + sqrt(Q), 1 / 3.) : - pow(q / 2. + sqrt(Q), 1 / 3.);
		y = z - p / 3. / z;
	}
	else // Q < 0, so complex numbers
	{
		double r = sqrt(abs(Q) + pow(q / 2., 2));
		double phi = atan2(sqrt(abs(Q)), - q / 2.);
		// ^(1/3)
		r = pow(r, 1 / 3.);
		phi /= 3.;
		assert(abs(r - abs(p) / 3. / r) < 2. * DBL_EPSILON);
		y = 2. * r * cos(phi);
	}
	double x = y - b / 3.;
	return x;
}

void PrintEquationRoot4(std::ostream &outStream, const EquationRoot4 & roots4Degree)
{
	outStream << std::fixed << std::setprecision(3) << "Equation have " << roots4Degree.numRoots << " root(s)"<< std::endl;
	for (size_t i = 0; i < roots4Degree.numRoots; ++i)
	{
		outStream << "\troot #" << i << " = " << roots4Degree.roots[i] << std::endl;
	}
}