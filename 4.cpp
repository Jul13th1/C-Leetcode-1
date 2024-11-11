/*
.删除链表的倒数第N个节点
输⼊：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]

定义快慢指针，快指针走n+1步
*/

#include <iostream>

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *removeNthForElement(ListNode *head,int n)
{
    //定义一个虚拟头结点 避免对头指针进行特殊判断
    ListNode *dummyHead = new ListNode(0);

    dummyHead->next = head;
    ListNode *slow = dummyHead;
    ListNode *fast = dummyHead;
    //快指针先走到n步，然后快慢指针再一起移动
    while(n-- && fast != nullptr)
    {
        fast = fast->next;
    }
    // 此时fast再提前⾛⼀步，因为需要让slow指向删除节点的上⼀个节点
    fast = fast->next;

    while(fast != nullptr)
    {
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = slow->next->next;

    return dummyHead->next;
}

// 打印链表
void printList(ListNode* head) 
{
    while (head != nullptr) 
    {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

// 主函数
int main() 
{
    // 创建链表: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    std::cout << "Original list: ";
    printList(head);

    // 删除倒数第n个节点
    ListNode* reversedHead = removeNthForElement(head,2);
    
    std::cout << "Reversed list: ";
    printList(reversedHead);

    return 0;
}