#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

int main()
{
    map<string, int> table{{"aaa", 1}, {"abc", 6}, {"hello", 10}};
    for(const pair<string, int> &t: table)
        cout << t.first << ": " << t.second << endl;

    return 0;
}
