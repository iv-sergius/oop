// Defines the entry point for the console application.

#include "stdafx.h"
#include "1-vector.h"

int main(int argv, const char * argc[])
{
	std::vector<double> vectorForTransform;
	vectorForTransform = readVectorFromStream(std::cin);
	if (vectorForTransform.empty())
	{
		std::cerr << "Can not read any double value from input" << std::endl;
		return 0;
	}
	transformVector(vectorForTransform);
	writeVectorToStream(vectorForTransform, std::cout);
	return 0;
}