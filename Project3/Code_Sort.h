#pragma once
#include <string>
using namespace std;

struct Code_Sort
{
    bool operator()(string i, string j)
    {
        i = i.substr(1);
        j = j.substr(1);
        return (i < j);
    }
};


struct String_Sort
{
    bool operator() (string i, string j)
    {
        return (i < j);
    }
};