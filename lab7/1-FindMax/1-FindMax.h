#pragma once
#include <functional>

template < typename T, typename Less = std::less<T> >
bool FindMaxEx(std::vector<T> const &arr, T& maxValue, Less & less = Less())
{
	if (arr.empty())
	{
		return false;
	}
	else
	{
		const T *max = &arr[0];
		for (size_t i = 1; i < arr.size(); ++i)
		{
			if (less(*max, arr[i]))
			{
				max = &arr[i];
			}
		}
		maxValue = *max;
		return true;
	}
}
