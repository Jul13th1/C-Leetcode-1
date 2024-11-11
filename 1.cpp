/*
用栈实现队列
*/

#include <iostream>
#include <stack>
#include <queue>

class MyQueue
{
public:
    std::stack<int> stIn;
    std::stack<int> stOut;

    void push(int x)
    {
        stIn.push(x);
    }
    //只有当stIn元素为空的时候，才将里面的元素弹入stOut

    int pop()
    {
        if(stOut.empty())
        {
            while(!stIn.empty())
            {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }
};