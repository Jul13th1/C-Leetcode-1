/*
环形链表
给定⼀个链表，返回链表开始⼊环的第⼀个节点。 如果链表⽆环，则返回 null。
1.判断是否有环
2.找到入口
*/

#include <iostream>

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *detechCycle(ListNode *head)
{
    ListNode *fast = head;
    ListNode *slow = head;
    while(fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
            //直到相遇
        if(slow == fast)
        {
            ListNode *index1 = fast;
            ListNode *index2 = head;

            while(index1 != index2)
            {
                index1 = index1->next;
                index2 = index2->next;
            }

            //返回环的入口
            return index2;
        }
    }
    return nullptr;
}

// 辅助函数：创建一个带环的链表
ListNode* createListWithCycle()
{
    // 创建链表节点
    ListNode* head = new ListNode(1);
    ListNode* second = new ListNode(2);
    ListNode* third = new ListNode(3);
    ListNode* fourth = new ListNode(4);

    head->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = second;  // 创建一个环，从第四个节点指回第二个节点

    return head;
}

void printResult(ListNode *head)
{
    ListNode* cycleStart = detechCycle(head);
    
    if (cycleStart)
        std::cout << "Cycle detected! The entry node is: " << cycleStart->val << std::endl;
    else
        std::cout << "No cycle detected." << std::endl;
}

int main() 
{
    // 创建带环的链表并测试
    ListNode* listWithCycle = createListWithCycle();
    printResult(listWithCycle);

    return 0;
}