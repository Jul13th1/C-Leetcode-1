/*
单链表中的指针域只能指向节点的下⼀个节点。
双链表：每⼀个节点有两个指针域，⼀个指向下⼀个节点，⼀个指向上⼀个节点。
双链表 既可以向前查询也可以向后查询
*/
/*
移除链表元素
head = [1,2,6,3,4,5,6], val = 6
输出：[1,2,3,4,5]
*/

#include <iostream>
// #include 
// 单链表
struct ListNode 
{
    int val; // 节点上存储的元素
    ListNode *next; // 指向下⼀个节点的指针
    ListNode(int x) : val(x), next(NULL) {} // 节点的构造函数
};

class Soltion
{
public:
    ListNode *removeElement(ListNode *head,int val)
    {
        //删除头结点
        while(head != NULL && head->val == val)
        {
            ListNode *tem = head;
            head = head->next;
            delete tem;
        }
        //删除非头结点
        ListNode *cur = head;
        while(cur != NULL && cur->next != NULL)
        {
            if(cur->next->val == val)
            {
                ListNode *tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }
            else
            {
                cur = cur->next;
            }
        }
        return head;
    }

    //设置一个虚拟头结点进行移除节点操作
    ListNode *removeElement1(ListNode *head,int val)
    {
        //设置一个虚拟头结点
        ListNode *dummyhead = new ListNode(0);
        //将虚拟头结点指向head
        dummyhead->next = head;

        ListNode *cur = dummyhead;
        while(cur->next != NULL)
        {
            if(cur->next->val == val)
            {
                ListNode *tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }
            else
            {
                cur = cur->next;
            }
        }
        head = dummyhead->next;
        delete dummyhead;
        delete head;
    }
};