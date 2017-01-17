#include "stdafx.h"
#include "2d.h"

int main()
{
	TypeShapePtrVector shapesVector;

	while (!std::cin.eof() && !std::cin.fail())
	{
		ReadShape(std::cin, shapesVector);
	}
	//PrintShape(shapesVector);
	PrintMaxAreaShape(shapesVector);
	PrintMinPerimeterShape(shapesVector);
	return 0;
}