/*
有效字母异位词
两个字符串 由相同的字母组成 顺序不同
*/

#include <iostream>
#include <string>

int main()
{
    std::string s1 = "hello";
    std::string s2 = "lloeh";

    int record[26] = {0};
    for(int i = 0; i < s1.size(); i++)
    {
        record[s1[i] - 'a']++;
    }
    for(int i = 0; i < s2.size(); i++)
    {
        record[s2[i] - 'a']--;
    }
    for(int i = 0; i < 26; i++)
    {
        if(record[i] != 0)
        {
            return false;
        }
    }
}

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

bool isAnagram(string s, string t) 
{
    // 如果两个字符串长度不同，直接返回 false
    if (s.length() != t.length())
    {
        return false;
    }

    // 哈希表来统计字符频率
    unordered_map<char, int> count_map;

    // 遍历第一个字符串，增加字符的频率
    for (char c : s) 
    {
        count_map[c]++;
    }

    // 遍历第二个字符串，减少字符的频率
    for (char c : t) 
    {
        count_map[c]--;
        // 如果某个字符频率为负数，说明该字符在 t 中出现次数比 s 中多，返回 false
        if (count_map[c] < 0) 
        {
            return false;
        }
    }

    // 如果所有字符的频率都相同，返回 true
    return true;
}

int main() {
    string s = "anagram";
    string t = "nagaram";

    if (isAnagram(s, t)) 
    {
        cout << "Yes, they are anagrams!" << endl;
    } else {
        cout << "No, they are not anagrams!" << endl;
    }

    return 0;
}