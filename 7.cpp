/*
旋转链表
1 2 3 4 5  k=2
3 4 5 1 2
*/

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        // 如果链表为空或只有一个节点，或者 k 为 0，直接返回原链表
        if (!head || !head->next || k == 0) {
            return head;
        }

        // 计算链表的长度
        ListNode* temp = head;
        int n = 1;
        while (temp->next) {
            temp = temp->next;
            n++;
        }

        // 归约 k 为 k % n
        k = k % n;
        if (k == 0) {
            return head; // 如果 k % n == 0，链表不需要旋转
        }

        // 将链表的尾部与头部连接，形成环
        temp->next = head;

        // 找到新的尾节点：它是第 n - k - 1 个节点
        ListNode* newTail = head;
        for (int i = 0; i < n - k - 1; i++) {
            newTail = newTail->next;
        }

        // 新的头节点是新的尾节点的 next
        ListNode* newHead = newTail->next;

        // 断开环，新的尾节点的 next 应该为 nullptr
        newTail->next = nullptr;

        return newHead;
    }
};