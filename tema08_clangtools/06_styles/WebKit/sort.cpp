#include "sort.hpp"

#include <algorithm>

void SelectionSort::sort(std::vector<int>& vec)
{
    for (std::vector<int>::iterator i = std::begin(vec); i != vec.end() - 1; i++)
        for (std::vector<int>::iterator j = i + 1; j != vec.end(); j++)
            if (!m_cmp(*i, *j))
                std::swap(*i, *j);
}

void QuickSort::sort(std::vector<int>& vec)
{
    std::sort(std::begin(vec), std::end(vec), m_cmp);
}