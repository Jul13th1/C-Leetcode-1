/*
给定⼀个 n 个元素有序的（升序）整型数组 nums 和⼀个⽬标值 target ，写⼀个函数搜索 nums 中的 target，如
果⽬标值存在返回下标，否则返回 -1

输⼊: nums = [-1,0,3,5,9,12], target = 9   输出: 4    
解释: 9 出现在 nums 中并且下标为 4
*/

#include <iostream>
#include <vector>

class Solution
{
public:
    int search(std::vector<int> &num,int target)
    {
        int left = 0;
        int right = num.size()-1;
        while(left <= right)
        {
            int mid = (left + right) / 2;

            if(num[mid] > target)
            {
                right = mid - 1;
            }
            else if(num[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                std::cout << mid << std::endl;
                return mid;
            }
        }

        return -1;
    }
};

int main()
{
    std::vector<int> num = {-1,0,3,5,9,12};

    Solution s;
    s.search(num,9);

    return 0;
}