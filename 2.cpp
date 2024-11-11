/*
队列实现栈
1 2 3 ----> 3 2 1
*/
#include <iostream>
#include <stack>
#include <queue>

class MyStack
{
public:
    std::queue<int> que;

    // 首先将元素放入到队列中
    void push(int x)
    {
        que.push(x);
    }
    //再进行弹出
    int pop()
    {
        int size = que1.size() - 1;
        //将队列的最后一个元素 之前的所有元素都重新加入到que队列中
        while(size--)
        {
            que.push(que.front());
            que.pop();
        }
        int result = que.front();
        que.pop();
        
        return result;
    }
};