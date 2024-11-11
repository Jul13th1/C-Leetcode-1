/*
两两交换链表的节点
1 2 3 4 ---> 2 1 4 3
*/

#include <iostream>

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


ListNode *swapPairs(ListNode *head)
{
    //设置一个虚拟头结点
    ListNode *dummyHead = new ListNode(0);
    //将虚拟头结点指向head
    dummyHead->next = head;

    ListNode *cur = dummyHead;

    while(cur->next != nullptr && cur->next->next != nullptr)
    {
        ListNode *temp = cur->next;
        ListNode *temp1 = cur->next->next->next;

        cur->next = cur->next->next;
        cur->next->next = temp;

        temp->next = temp1;
        cur = cur->next->next;
    }
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
int main() {
    // 创建链表: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    std::cout << "Original list: ";
    printList(head);

    // 反转两两链表
    ListNode* reversedHead = swapPairs(head);
    
    std::cout << "Reversed list: ";
    printList(reversedHead);

    return 0;
}