/*
给你⼀个按 ⾮递减顺序 排序的整数数组 nums，返回 每个数字的平⽅ 组成的新数组，要求也按 ⾮递减顺序 排
序。
示例 1：
输⼊：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平⽅后，数组变为 [16,1,0,9,100]，排序后，数组变为 [0,1,9,16,100]
*/

#include <iostream>
#include <vector>

class Solution
{
public:
    //暴力排序
    std::vector<int> sortAquares(std::vector<int> &A)
    {
        for(int i = 0; i < A.size(); i++)
        {
            A[i] *= A[i];
        }

        // A.sort(A.begin(),A.end());

        return A;
    }

    //双指针法
    // 定义⼀个新数组result，和A数组⼀样的⼤⼩，让k指向result数组终⽌位置。
    // 如果 A[i] * A[i] < A[j] * A[j] 那么 result[k--] = A[j] * A[j]; 。
    // 如果 A[i] * A[i] >= A[j] * A[j] 那么 result[k--] = A[i] * A[i];

    std::vector<int> SortArray(std::vector<int> &num)
    {
        int k = num.size()-1;
        std::vector<int> result(num.size(),0);
        for(int i = 0,j =  k; i <= j;)
        {
            if(num[i] * num[i] < num[j]*num[j])
            {
                result[k--] = num[j]*num[j];
                j--;
            }
            else
            {
                result[k--] = num[i] * num[i];
                i++;
            }
        }

        return result;
    }
};

int main()
{
    std::vector<int> num1 = {-4,-1,0,3,10};

    Solution s;
    std::vector<int> num = s.SortArray(num1);

    for(auto it = num.begin(); it < num.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}