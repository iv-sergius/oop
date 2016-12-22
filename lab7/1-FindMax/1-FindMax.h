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
		const T &max = arr[0];
		for (auto & item : arr )
		{
			if (less(max, item))
			{
				const_cast<T&>(max) = item;
			}
		}
		maxValue = max;
		return true;
	}
}
