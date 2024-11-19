/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 * 
 * 删除链表重复元素
 * 1 2 2 3 3 4 ----> 1 4
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *virtualhead = new ListNode(0);
        virtualhead->next = head;

        ListNode *cur = virtualhead;
        while(cur->next != nullptr && cur->next->next != nullptr)
        {
            if(cur->next->val == cur->next->next->val)
            {
                int samevalue = cur->next->val;
                while(cur->next && cur->next->val == samevalue)
                {
                    cur->next = cur->next->next;
                }
            }
            else
            {
                cur = cur->next;
            }
        }
        return virtualhead->next;
    }
};