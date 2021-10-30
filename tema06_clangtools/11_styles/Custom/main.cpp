#include "sort.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

void vprint(const std::vector<int> &vec)
{
	for (std::vector<int>::const_iterator it = vec.cbegin();
	     it != vec.cend(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int main()
{
	std::vector<int> vec{5, 3, 1, 4, 2};
	auto vec_copy = vec;

	auto asc = [](int a, int b) { return a < b; };
	auto desc = [](int a, int b) { return a > b; };

	QuickSort qs(asc);
	SelectionSort ss(desc);

	qs.sort(vec);
	ss.sort(vec_copy);

	vprint(vec);
	vprint(vec_copy);

	return 0;
}