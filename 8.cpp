/*
给你⼀个数组 nums 和⼀个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新⻓度。
不要使⽤额外的数组空间，你必须仅使⽤ O(1) 额外空间并原地修改输⼊数组。

给定 nums = [0,1,2,2,3,0,4,2], val = 2,
函数应该返回新的⻓度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。
*/
// 是两层for循环，⼀个for循环遍历数组元素 ，第⼆个for循环更新数组。

#include <iostream>
#include <vector>

class Solution
{
public:

    //两层for循环法 ⼀个for循环遍历数组元素 ，第⼆个for循环更新数组。
    int removeElement(std::vector<int> &num,int val)
    {
        int size = num.size();
        for(int i = 0; i < size; i++)
        {
            if(num[i] == val)
            {
                for(int j = i + 1; j < size; j++)
                {
                    num[j - 1] = num[j];
                }
                i--;
                size--;
            }
        }
        return size;
    }

    //双指针法
    // 通过⼀个快指针和慢指针在⼀个for循环下完成两个for循环的⼯作。
    // 快指针：寻找新数组的元素 ，新数组就是不含有⽬标元素的数组
    // 慢指针：指向更新 新数组下标的位置

    int removeElement1(std::vector<int> &num,int val)
    {
        int slowIndex = 0;
        for(int fastIndex = 0; fastIndex < num.size(); fastIndex++)
        {
            if(num[fastIndex] != val)
            {
                num[slowIndex++] = num[fastIndex]; 
            }
        }
        return slowIndex;
    }

    
};