/*
给定⼀个含有 n 个正整数的数组和⼀个正整数 s ，找出该数组中满⾜其和 ≥ s 的⻓度最⼩的 连续 ⼦数组，并返回
其⻓度。如果不存在符合条件的⼦数组，返回 0。

输⼊：s = 7, nums = [2,3,1,2,4,3]
输出：2
*/
#include <iostream>
#include <vector>

class Solution
{
public:
    //暴⼒解法当然是 两个for循环，然后不断的寻找符合条件的⼦序列
    int minSubArrayLen(int s,std::vector<int> &num)
    {
        int result = INT32_MAX; //最终结果
        int sum = 0;    //子序列的数值之和
        int Length = 0; //子序列长度

        for(int i = 0; i < num.size(); i++)
        {
            sum = 0;
            for(int j = i; j < num.size(); j++)
            {
                sum += num[j];
                //⼀旦发现⼦序列和超过了s，更新result
                if(sum > s)
                {
                    Length = j - i + 1;
                    result = result < Length? result : Length;
                    break;
                }
            }
        }
        return result == INT32_MAX ? 0 : result;
    }
};