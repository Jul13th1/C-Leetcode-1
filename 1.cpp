/*
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
输入: nums = [1,3,5,6], target = 5
输出: 2
*/

#include <iostream>
#include <vector>

class Sulation
{
public:
    int SearchIndex(std::vector<int> nums,int target)
    {
        int left = 0;
        int right = nums.size()-1;
        while(left <= right)
        {
            int mid = (left+right)/2;
            if(nums[mid] >= target)
            {
                right = mid-1;
            }
            else
            {
                left = mid+1;
            }
        }

        std::cout << left << std::endl;
        return left;
    }
};

int main()
{
    Sulation s;
    std::vector<int> nums = {1,2,3,4,5};
    int target = 2;

    s.SearchIndex(nums,target);

    return 0;
}