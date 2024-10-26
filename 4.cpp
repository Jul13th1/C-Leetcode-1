/*
轮转数组
输入: nums = [1,2,3,4,5,6,7], k = 3
输出: [5,6,7,1,2,3,4]

void rotate(std::vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n; // 处理 k 大于 n 的情况
    std::reverse(nums.begin(), nums.end()); // 反转整个数组
    std::reverse(nums.begin(), nums.begin() + k); // 反转前 k 个元素
    std::reverse(nums.begin() + k, nums.end()); // 反转后 n-k 个元素
}
*/