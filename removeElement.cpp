/*
    设定一个数组有一系列元素【1，3，4，5，5，5，6】
    给一个数为5
    数组有4个不与数组相同的数
    所以函数返回4
    class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
    
        int i = 0;
        for(int n : nums)
        {
            if(n != val)
            {
                nums[i] = n;
                i++;
            }
        }
        return i;
    }
};
*/