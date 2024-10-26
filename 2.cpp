/*
    删除有序数组的重复项
    [0,0,1,1,1,2,2,3,3,4] ----> [0,1,2,3,4]
    class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.size() < 2)
        {
            return nums.size();
        }
        int num = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] != nums[i+1])
            {
                nums[++num] = nums[i+1];
            }
        }
        return num;
    }
};
*/