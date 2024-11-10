/*
反转链表
*/

#include <iostream>
#include <stack>

// 定义链表节点
//1. 使用双指针法（迭代法）
// 双指针法的核心思路是逐步反转链表的指针，使得每个节点指向它的前一个节点，直到整个链表反转。
struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 双指针法（迭代）
ListNode* reverseList(ListNode* head) 
{
    ListNode* prev = nullptr;  // 初始化为nullptr，表示反转后的链表尾部
    ListNode* curr = head;     // 当前节点指向头节点

    while (curr != nullptr) 
    {
        ListNode* nextTemp = curr->next;  // 暂存当前节点的下一个节点
        curr->next = prev;  // 将当前节点的指针反转
        prev = curr;        // prev指向当前节点
        curr = nextTemp;    // 移动到下一个节点
    }
    return prev;  // prev现在指向新链表的头节点
}

// 递归法
// 递归法的核心思想是将问题分解成更小的子问题。我们反转链表的后半部分，再把当前节点的指针指向它的前一个节点，最终完成整个链表的反转。
ListNode* reverseListRecursive(ListNode* head) 
{
    if (head == nullptr || head->next == nullptr) 
    {
        return head;  // 基本情况，链表为空或只有一个节点，直接返回
    }

    ListNode* reversedList = reverseListRecursive(head->next);  // 递归反转链表
    head->next->next = head;  // 将当前节点指向前一个节点
    head->next = nullptr;     // 将当前节点的next指针置为nullptr

    return reversedList;  // 返回反转后的链表头节点
}

// 使用栈法
// 栈法的核心思想是利用栈的后进先出（LIFO）特性，将链表节点依次压入栈中，最后出栈时便实现了链表的反转。
// 栈法
ListNode* reverseListUsingStack(ListNode* head) 
{
    std::stack<ListNode*> nodeStack;

    // 将链表节点压入栈中
    while (head != nullptr) 
    {
        nodeStack.push(head);
        head = head->next;
    }

    if (nodeStack.empty()) 
    {
        return nullptr;
    }

    // 获取栈顶元素作为新链表的头
    ListNode* reversedHead = nodeStack.top();
    nodeStack.pop();

    ListNode* curr = reversedHead;
    // 弹出栈中的每个元素，并更新指针
    while (!nodeStack.empty()) 
    {
        curr->next = nodeStack.top();
        nodeStack.pop();
        curr = curr->next;
    }
    curr->next = nullptr;  // 最后一个节点的next指针设为nullptr

    return reversedHead;
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

    // 反转链表
    ListNode* reversedHead = reverseList(head);
    
    std::cout << "Reversed list: ";
    printList(reversedHead);

    return 0;
}