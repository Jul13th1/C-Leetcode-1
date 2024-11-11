/*
反转字符串
示例 1： 
输⼊：["h","e","l","l","o"] 
输出：["o","l","l","e","h"]
*/
// swap两种交换数值
/*
第一种：引用或者指针
int tmp = s[i];
s[i] = s[j];
s[j] = tmp;
第二种：位运算
s[i] ^= s[j];
s[j] ^= s[i];
s[i] ^= s[j];
*/
#include <iostream>
#include <vector>

void reverseString(std::vector<char> &s)
{
    for(int i = 0,j = s.size()-1;i < s.size()/2; i++,j--)
    {
        std::swap[s[i],s[j]];
    }
}