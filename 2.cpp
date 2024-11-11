/*
反转字符串2
输⼊: s = "abcdefg", k = 2 
输出: "bacdfeg"
*/

#include <iostream>
#include <string>
#include <vector>

std::string reverseStr(std::string s,int k)
{
    for(int i = 0; i < s.size(); i += (2*k))
    {
        if(i + k <= s.size())
        {
            s.reserve(s.begin()+i,s.begin()+i+k);
        }
        else
        {
            s.reverse(s.begin()+i,s.end());
        }
    }
    return s;
}