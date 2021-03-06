// Defines the entry point for the console application.

#include "stdafx.h"
#include "1-vector.h"
#include <algorithm>

int main(int argv, const char * argc[])
{
	std::vector<double> vectorForTransform;
	vectorForTransform = ReadVectorFromStream(std::cin);
	if (vectorForTransform.empty())
	{
		std::cerr << "Can not read any double value from input" << std::endl;
		return 0;
	}
	TransformVector(vectorForTransform);
	std::vector<double> sortedVector;
	sortedVector = vectorForTransform;
	std::sort(sortedVector.begin(), sortedVector.end());
	WriteVectorToStream(vectorForTransform, std::cout);
	return 0;
}