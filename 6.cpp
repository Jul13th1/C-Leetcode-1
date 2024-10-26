/*
    给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。
    判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
    示例 1：
    输入：nums = [2,3,1,1,4]
    输出：true
    解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
*/

#include <iostream>
#include <vector>

bool canJump(std::vector<int>& nums) {
    int maxReach = 0; // 初始化最大可达索引
    int n = nums.size();

    for (int i = 0; i < n; ++i) {
        if (i > maxReach) {
            // 如果当前位置超出了可达范围，返回 false
            return false;
        }
        // 更新最大可达索引
        maxReach = std::max(maxReach, i + nums[i]);
        if (maxReach >= n - 1) {
            // 如果可以到达最后一个索引，返回 true
            return true;
        }
    }
    return false; // 如果遍历结束都未能到达最后一个索引
}

int main() {
    std::vector<int> nums = {2, 3, 1, 1, 4};
    if (canJump(nums)) {
        std::cout << "可以到达最后一个下标" << std::endl;
    } else {
        std::cout << "无法到达最后一个下标" << std::endl;
    }

    return 0;
}