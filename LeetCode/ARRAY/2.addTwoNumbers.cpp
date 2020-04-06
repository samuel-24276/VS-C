#include<iostream>
#include<vector>

using namespace std;

/**
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
*/


struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        int data[100];
        int i;
        int carry = 0;
        for(i=0; l1!=NULL && l2!=NULL; ++i)
        {
            data[i] = l1->val + l2->val + carry;
            if(data[i] >= 10)
            {
                carry = data[i] / 10;
                data[i] = data[i] % 10;
            }
            else    carry = 0;
            l1 = l1->next;
            l2 = l2->next;
        }
        for(; l1; l1 = l1->next, i++)
        {
            data[i] = l1->val + carry;
            carry = data[i] / 10;
            if(carry)
                data[i] = data[i] % 10;
        }
        for(; l2; l2 = l2->next, i++)
        {
            data[i] = l2->val + carry;
            carry = data[i] / 10;
            if(carry)
                data[i] = data[i] % 10;
        }
        if(carry)
            data[i++] = carry;
        ListNode *L = new ListNode(data[0]);
        ListNode *T;
        T = L;
        for(int j= 1; j<i; ++j)
        {
            ListNode *N = new ListNode(data[j]);
            T->next = N;
            T = T->next;
        }
        return L;
    }
};

int main()
{
    ListNode *a = new ListNode(9);
    ListNode *b = new ListNode(3);
    //ListNode *c = new ListNode(5);
    ListNode *d = new ListNode(9);
    ListNode *e = new ListNode(4);
    ListNode *f = new ListNode(6);
    b->next = a;
    //c->next = b;
    e->next = d;
    f->next = e;
    Solution sol;
    ListNode *L = sol.addTwoNumbers(b,f);
    while(L->next)
    {
        cout<<L->val<<"->";
        L = L->next;
    }
    cout<<L->val<<endl;
    delete [] L;
    system("pause");
    return 0;
}

/**
执行用时 :中等难度
32 ms, 在所有 C++ 提交中击败了51.51%的用户
内存消耗 :
10.3 MB, 在所有 C++ 提交中击败了84.13%的用户
2020.01.04
**/
