#pragma once

template < typename T, typename Less >
bool FindMaxEx(std::vector<T> const &arr, T& maxValue, Less & less)
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

template < typename T>
bool FindMaxEx(std::vector<T> const &arr, T& maxValue)
{
	if (arr.empty())
	{
		return false;
	}
	else
	{
		T const *max = &arr[0];
		for (size_t i = 1; i < arr.size(); ++i)
		{
			if (*max < arr[i])
			{
				max = &arr[i];
			}
		}
		maxValue = *max;
		return true;
	}
}
