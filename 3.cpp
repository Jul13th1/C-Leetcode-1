/*
两数之和
nums = [2, 7, 11, 15], target = 9
因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]
*/

#include <iostream>
#include <vector>
#include <unordered_map>

class Solution 
{
public:
    std::vector<int> twoSum(vector<int>& nums, int target) 
    {
        std::unordered_map <int,int> map;
        for(int i = 0; i < nums.size(); i++) 
        {
            // 遍历当前元素，并在map中寻找是否有匹配的key
            auto iter = map.find(target - nums[i]);
            if(iter != map.end()) 
            {
                return {iter->second, i};
            }
            // 如果没找到匹配对，就把访问过的元素和下标加⼊到map中
            map.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }
};