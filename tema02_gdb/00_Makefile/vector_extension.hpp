#include <vector>
#include <iostream>

std::vector<int> load(std::istream& input);

void store(const std::vector<int>& v, std::ostream& output);

void transfer(std::istream& input, std::ostream& output);

std::vector<int> drop_duplicates(const std::vector<int>& v);

unsigned nduplicates(const std::vector<int>& v);

unsigned nunique(const std::vector<int>& v);
