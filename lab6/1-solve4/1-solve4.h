#include "stdafx.h"

struct EquationRoot2
{
	size_t numRoots;
	double roots[2];
};

// ¬ычисл€ет корни кубического уравнени€ ax^2 + bx + c= 0
EquationRoot2 Solve2(double a, double b, double c);

struct EquationRoot4
{
	size_t numRoots;
	double roots[4];
};

// ¬ычисл€ет корни кубического уравнени€ ax^4 + bx^3 + cx^2 + dx + e = 0
EquationRoot4 Solve4(double a, double b, double c, double d, double e);

// find one of roots of 3rd derge equations
double Root3(double a, double b, double c, double d);

void PrintEquationRoot4(std::ostream &outStream, const EquationRoot4 & roots4Degree);
