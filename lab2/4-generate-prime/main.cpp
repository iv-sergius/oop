#include "stdafx.h"
#include "4-generate-prime.h"
#include <sstream>
#include <ctime>

void WriteSet(const std::set<size_t> &anySet)
{
	for (std::set<size_t>::iterator iterator = anySet.begin(); iterator != anySet.end(); ++iterator)
	{
		std::cout << *iterator << ' ';
	}
	std::cout << std::endl;
}

int main(int argv, char * argc[])
{
	if (argv != 2)
	{
		std::cerr << "Invalid arguments amount" << std::endl
			<< "Usage generate_prime.exe <upper bound>" << std::endl;
		return 1;
	}
	int upperBound;
	if (!(std::istringstream(argc[1]) >> upperBound))
	{
		std::cerr << "Upper bound must be numeric" << MAX_UPPER_BOUND << std::endl;
		return 2;
	}
	
	if (upperBound < MAX_UPPER_BOUND)
	{
		std::set<size_t> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);	
		WriteSet(primeNumbersSet);
	}

	return 0;
}
