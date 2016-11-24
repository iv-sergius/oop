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

std::set<size_t> GenerateSetOfPrimes(size_t upperBound)
{
	std::set<size_t> primesSet;

	if (IsUpperBoundInLimits(upperBound))
	{
		if (upperBound > 1)
		{
			primesSet.insert(2);
		}
		std::vector<bool> flagIfPrime(upperBound + 1, true);
		size_t candidateInPrime = 3;
		for (candidateInPrime = 3; candidateInPrime <= upperBound; candidateInPrime += 2)
		{
			if (flagIfPrime[candidateInPrime])
			{
				primesSet.insert(primesSet.end(), candidateInPrime);
				SiftPrimeNumber(candidateInPrime, flagIfPrime, upperBound);
			}
		}
	}
	return primesSet;
}