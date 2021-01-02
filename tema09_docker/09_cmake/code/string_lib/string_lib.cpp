#include "string_lib.hpp"
#include <iostream>
std::vector<std::string> split(const std::string& text, const char delimiter)
{
    std::vector<std::string> words;
    unsigned start = 0;
    auto it = std::begin(text);
    do
    {
        it = std::find(it, std::end(text), delimiter);
        unsigned pos = it - std::begin(text) + 1;
        unsigned len = pos - start - 1;

        if(len > 0)
            words.push_back(text.substr(start, len));

        start = pos;
        if(it != std::end(text))
            it++;
    }
    while (it != std::end(text));
    return words;
}