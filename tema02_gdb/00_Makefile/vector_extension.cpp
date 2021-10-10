#include "vector_extension.hpp"

std::vector<int> load(std::istream& input)
{
    std::vector<int> v;
    int value;
    while(input >> value)
        v.push_back(value);
    return v;
}

void store(const std::vector<int>& v, std::ostream& output)
{
    for(int value: v)
        output << value << " ";
}

void transfer(std::istream& input, std::ostream& output)
{
    store(load(input), output);
}

std::vector<int> drop_duplicates(const std::vector<int>& v)
{
    unsigned n = v.size();

    std::vector<int> result;
    for(unsigned i=0; i<n; i++)
    {
        bool add = true;
        for(unsigned j=0; j<i-1; j++)
        {
            if(v[i] == v[j])
            {
                add = false;
                break;
            }
        }
        if(add)
            result.push_back(v[i]);
    }
    return result;
}

unsigned nduplicates(const std::vector<int>& v)
{
    auto v_unq = drop_duplicates(v);
    return v.size() - v_unq.size();
}

unsigned nunique(const std::vector<int>& v)
{
    return v.size() - nduplicates(v);
}
