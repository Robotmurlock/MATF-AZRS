#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "sort.hpp"

void vprint(const std::vector<int>& vec)
{
    for(int it : vec)
        std::cout << it << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector<int> vec{5, 3, 1, 4, 2};
    auto vec_copy = vec;

    auto asc = [](int a, int b){return a < b;};
    auto desc = [](int a, int b){return a > b;};

    QuickSort qs(asc);
    SelectionSort ss(desc);

    qs.sort(vec);
    ss.sort(vec_copy);

    vprint(vec);
    vprint(vec_copy);

    return 0;
}
