#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <vector>

void bruteforce(const std::string& filename, const std::string& pattern)
{
    std::ifstream input(filename);
    std::stringstream stream;
    std::string word;

    int count = 0;
    while(input >> word)
    {
        for(size_t i=0; i<word.size(); i++)
        {
            bool match = true;
            for(size_t j=0; j<pattern.size(); j++)
            {
                if(word[i+j] != pattern[j])
                {
                    match = false;
                    break;
                }
            }
            if(match)
                count++;
        }
    }
    

    std::cout << "[bruteforce]: count=" << count << std::endl;
    input.close();
}

std::vector<int> kmp_form_lps(const std::string& pattern)
{
    size_t n = pattern.size();
    std::vector<int> lps(n, 0);
    int i=1;
    int j=0;
    while(i<n)
    {
        if(pattern[i] == pattern[j])
        {
            j++;
            lps[i] = j;
            i++;
        }
        else if(j > 0)
        {
            j = lps[j-1];
        }
        else
        {
            i++;
        }
    }
    return lps;
}

void kmp(const std::string& filename, const std::string& pattern)
{
    std::ifstream input(filename);
    std::stringstream stream;
    std::string word;

    int count = 0;
    auto lps = kmp_form_lps(pattern);
    while(input >> word)
    {
        int j = 0, i = 0;
        while(i < word.size())
        {
            if(word[i] == pattern[j])
            {
                i++;
                j++;
            
                if(j == pattern.size())
                {
                    count++;
                    j = lps[j-1];
                }
            }
            else if(j > 0)
            {
                j = lps[j-1];
            }
            else
            {
                i++;
            }
        }
    }
    std::cout << "[kmp]: count=" << count << std::endl;
    input.close();
 
}

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cerr << "Usage: ./program [filename] [pattern]" << std::endl;
        return -1;
    }
    std::string filename(argv[1]);
    std::string pattern(argv[2]);

    bruteforce(filename, pattern);
    kmp(filename, pattern);

    return 0;
}
