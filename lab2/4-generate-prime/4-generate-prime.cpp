// 4-generate-prime.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "4-generate-prime.h"
#include <cmath>
#include <vector>
#include <iostream>

bool IsUpperBoundInLimits(size_t upperBound)
{
	return upperBound > 1 && upperBound <= MAX_UPPER_BOUND;
}

//size_t GetSizeOfPrimeNumbersSet(size_t upperBound)
//{
//	size_t calculatedSize = (size_t) 2 * upperBound / log(upperBound);
//	return (calculatedSize < MAX_PRIME_AMOUNT) ? calculatedSize : MAX_PRIME_AMOUNT;
//}

void SiftPrimeNumber(size_t primeNumber, std::vector<bool> &primeNumbersSieve, size_t upperBound)
{
	for (size_t k = primeNumber * primeNumber; k <= upperBound; k += 2 * primeNumber)
	{
		primeNumbersSieve[k] = false;
	}
}

std::set<size_t> GeneratePrimeNumbersSet(size_t upperBound)
{
	std::set<size_t> resultSetWithPrimeNumbers;

	if (IsUpperBoundInLimits(upperBound))
	{
		resultSetWithPrimeNumbers.insert(2);
		if (upperBound > 2)
		{
			resultSetWithPrimeNumbers.insert(resultSetWithPrimeNumbers.end(), 3);
			std::vector<bool> primeNumbersSieve(upperBound + 1, true);
			SiftPrimeNumber(3, primeNumbersSieve, upperBound);
			size_t candidateInPrime = 5;
			for (candidateInPrime = 5; candidateInPrime <= upperBound; candidateInPrime += 2)
			{
				if (primeNumbersSieve[candidateInPrime])
				{
					resultSetWithPrimeNumbers.insert(resultSetWithPrimeNumbers.end(), candidateInPrime);
					SiftPrimeNumber(candidateInPrime, primeNumbersSieve, upperBound);
				}
			}
		}
	}
	return resultSetWithPrimeNumbers;
}