/*
输入：nums = [2,2,1,1,1,2,2]
输出：2

给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int num = nums[0];
        int count = 0;
        for(int i = 1; i < nums.size(); i++)
        {
            if(num == nums[i])
            {
                count++;
            }
            else
            {
                count--;
                if(count == 0)
                {
                    num = nums[i];
                }
            }
        }
        return num;
    }
};
*/