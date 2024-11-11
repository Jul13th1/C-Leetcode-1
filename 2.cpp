/*
两个数组的交集
如 nums1[4 9 5] nums2[9 4 9 8 4] ----->[9 4]
*/

//1.使用set
#include <iostream>
#include <unordered_set>
#include <vector>

std::vector<int> intersection(std::vector<int> &nums1,std::vector<int> &nums2)
{
    //保存结果
    std::unordered_set<int> result_set;
    std::unordered_set<int> nums_set(nums1.begin(),nums1.end());

    for(int num : nums2)
    {
        if(nums_set.find(num) != nums_set.end())
        {
            result_set.insert(num);
        }
    }
    return std::vector<int>(result_set.begin(),result_set.end());
}

//使用数组
vector<int> intersection1(vector<int>& nums1, vector<int>& nums2) 
{
    unordered_set<int> result_set; // 存放结果，之所以⽤set是为了给结果集去重
    int hash[1005] = {0}; // 默认数值为0
    for (int num : nums1) 
    { // nums1中出现的字⺟在hash数组中做记录
        hash[num] = 1;
    }
    for (int num : nums2) 
    { // nums2中出现话，result记录
        if (hash[num] == 1) 
        {
            result_set.insert(num);
        }
    }
    return vector<int>(result_set.begin(), result_set.end());
 }

void printVector(const std::vector<int>& vec) 
{
    for (int num : vec) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() 
{
    std::vector<int> nums1 = {1, 2, 2, 1};
    std::vector<int> nums2 = {2, 2};

    std::vector<int> result = intersection(nums1, nums2);

    // 打印结果
    printVector(result);

    return 0;
}