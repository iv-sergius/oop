#include "stdafx.h"
#include "2d.h"

int main()
{
	
	TypeShapePtrVector shapesVector;
	TypeShapePtr shareIShapePtr;
	
	shapesVector.push_back(shareIShapePtr);
	
	
	while (!std::cin.eof() && !std::cin.fail())
	{
		ReadShape(std::cin, shapesVector);
	}
	PrintShape(shapesVector);
	//PrintMaxAreaShape(shapesVector);
	//PrintMinPerimeterShape(shapesVector);
	return 0;
}