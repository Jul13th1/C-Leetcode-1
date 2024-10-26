/*
买股票的最佳时期 I
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int naxn = 0;
        int minn = prices[0];
        for(int i = 0; i < prices.size(); i++)
        {
            minn = min(minn,prices[i]);
            naxn = max(naxn,prices[i] - minn);
        }
        return naxn?naxn:0;
    }
};

买股票最佳时期II
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。
返回 你能获得的 最大 利润 。
输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4。
随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3。
最大总利润为 4 + 3 = 7 。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int num = 0;
        for(int i = 1; i < prices.size(); i++)
        {
            if(prices[i] > prices[i-1])
            {
                num += prices[i] - prices[i-1];
            }
        }
        return num;
    }
};

*/