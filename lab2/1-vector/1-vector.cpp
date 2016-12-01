// 1-vector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "1-vector.h"
#include <algorithm>
#include <functional>
#include <numeric>

std::vector<double> ReadVectorFromStream(std::istream & inStream)
{
	return{ std::istream_iterator<double>(inStream), std::istream_iterator<double>() };
}

void WriteVectorToStream(std::vector<double> const & vectorToOut, std::ostream & outStream)
{
	outStream << std::fixed << std::setprecision(3);
	std::ostream_iterator<double> outIterator(outStream, " ");
	std::copy(vectorToOut.begin(), vectorToOut.end(), outIterator);
	outStream << std::endl;
}

// task 5	
void TransformVector(std::vector<double> & vector)
{
	if (vector.empty())
	{
		return;
	}
	double sumOfNonNegative = std::accumulate(vector.begin(), vector.end(), 0.0, [](double sum, double element) {
		return sum += (element > 0) ? element : 0;
	});
	bool isEven = false;
	std::transform(vector.begin(), vector.end(), vector.begin(), [&](double element) {
		isEven = !isEven;
		if (isEven)
		{
			return element * 2.0;
		}
		else
		{
			return element - sumOfNonNegative;
		}
	});

}