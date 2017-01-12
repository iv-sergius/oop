// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "1-solve4.h"

int main()
{
	std::cout << "Enter 5 coeff of 4th degree equations (start with higher degree)" << std::endl;
	double a, b, c, d, e;
	EquationRoot4 root4degree;
	while ((std::cin >> a) && (std::cin >> b) && (std::cin >> c) && (std::cin >> d) && (std::cin >> e))
	{
		try
		{
			root4degree = Solve4(a, b, c, d, e);
			PrintEquationRoot4(std::cout, root4degree);
		}
		catch (const std::exception &ex)
		{
			std::cout << "Error: " << ex.what() << std::endl;
		}
	}
	return 0;
}
