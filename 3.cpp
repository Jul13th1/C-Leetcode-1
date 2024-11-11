/*
翻转字符串的单词
示例 1：
输⼊: "the sky is blue" 
输出: "blue is sky the

源字符串为："the sky is blue "
移除多余空格 : "the sky is blue"
字符串反转："eulb si yks eht"
单词反转："blue is sky the"
*/
#include <iostream>
#include <string>
#include <algorithm>  // 引入 swap 函数

class Solution {
public:
    // 反转字符串中的一个部分
    void reverse(std::string &s, int start, int end) 
    {
        for (int i = start, j = end; i < j; i++, j--) 
        {
            std::swap(s[i], s[j]);  // 使用 std::swap 来交换字符
        }
    }

    // 去除多余的空格并保持单词之间有一个空格
    void removeExtra(std::string &s) 
    {
        int slow = 0;
        for (int i = 0; i < s.size(); i++) 
        {
            if (s[i] != ' ') 
            {  // 不是空格字符
                if (slow != 0) 
                {  // 不是第一个单词
                    s[slow++] = ' ';  // 在单词之间添加空格
                }
                while (i < s.size() && s[i] != ' ') 
                {  // 复制单词
                    s[slow++] = s[i++];
                }
            }
        }
        s.resize(slow);  // 调整字符串大小，去除多余的空格
    }

    // 反转字符串中的每个单词
    std::string reverseWords(std::string &s) 
    {
        removeExtra(s);  // 去除多余的空格
        reverse(s, 0, s.size() - 1);  // 反转整个字符串

        int start = 0;
        for (int i = 0; i < s.size(); i++) 
        {
            if (s[i] == ' ') 
            {  // 找到单词边界
                reverse(s, start, i - 1);  // 反转当前单词
                start = i + 1;  // 更新下一个单词的起始位置
            }
        }
        reverse(s, start, s.size() - 1);  // 反转最后一个单词
        return s;
    }
};

int main() 
{
    Solution sol;
    std::string input = "  the  sky is   blue";
    std::string output = sol.reverseWords(input);
    std::cout << "Reversed words: " << output << std::endl;  // 输出反转后的单词顺序
    return 0;
}