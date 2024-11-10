/*
螺旋矩阵
给定⼀个正整数 n，⽣成⼀个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的正⽅形矩阵。
示例:
输⼊: 3
输出:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/

/*
思路
填充上⾏从左到右
填充右列从上到下
填充下⾏从右到左
填充左列从下到上
*/

#include <iostream>
#include <vector>

class Solution
{
public:
    std::vector<std::vector<int>> generateMatrix(int n)
    {
        //首先定义一个二维数组
        std::vector<std::vector<int>> res(n,std::vector<int>(n,0));
        //定义每循环一圈的起始位置
        int startx,starty = 0;
        int loop = n / 2;
        //矩阵的中间位置
        int mid = n /2;

        //用来给矩阵每个空格赋值
        int count = 1;
        //需要控制每⼀条边遍历的⻓度，每次循环右边界收缩⼀位
        int offset = 1;

        int i,j;
        while(loop--)
        {
            i = startx;
            j = starty;
            // 下⾯开始的四个for就是模拟转了⼀圈

            // 模拟填充上⾏从左到右(左闭右开)
            for(j = starty;j < n-offset; j++)
            {
                res[startx][j] = count++;
            }
            // 最左边上到下
            for(i = startx; i < n-offset; i++)
            {
                res[i][j] = count++;
            }
            // 最下面右到左
            for(;j > starty; j--)
            {
                res[i][j] = count++;
            }
            for(; i > startx; i--)
            {
                res[i][j] = count++;
            }
            //第二圈起始位置都要加1
            //例如：第⼀圈起始位置是(0, 0)，第⼆圈起始位置是(1, 1)

            startx++;
            starty++;
            // offset 控制每⼀圈⾥每⼀条边遍历的⻓度
            offset += 1;
        }
        // 如果n为奇数的话，需要单独给矩阵最中间的位置赋值
        if (n % 2) 
        {
            res[mid][mid] = count;
        }

        return res;
    }
};