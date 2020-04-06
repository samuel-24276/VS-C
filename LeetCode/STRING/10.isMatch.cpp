#include<iostream>
#include<string>

using namespace std;

/*
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

说明:

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
示例 1:

输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:

输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
示例 3:

输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
示例 4:

输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
示例 5:

输入:
s = "mississippi"
p = "mis*is*p*."
输出: false
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        int s_size = s.size(), p_size = p.size();
        int size = s_size < p_size ? s_size : p_size;       //size取较小的那个

        if (size == 0)      //s,p均为空
            return true;
        if (s_size == 0) { //s空，p不空
            for (int i = 0; i < p_size; ++i)    //p中只要不全是*则无法匹配
                if (p[i] != '*')
                    return false;
        }
        if (p_size == 0) {  //p空，s不空
            for (int i = 0; i < s_size; ++i)    //s中只要不全是*则无法匹配
                if (s[i] != '*')
                    return false;
        }

        /*注意实例4*/
        //s,p均不为空
        for (int i = 0; i < size; ++i) {
            for (int j = i; j < size; ++j) {
                if (s[i] == p[i])
                    continue;
                else {  //若不相等，则说明P中出现.或者*
                    if (p[i] == '.')
                        continue;
                    else {  //p[i]=='*'

                    }
                }
            }
            
        }
    }
};

int main() {
    system("pause");
	return 0;
}