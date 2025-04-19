/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    public:
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            ListNode* result = new ListNode(0);
            ListNode* current = result;
            int carry = 0;
            while (l1 != nullptr || l2 != nullptr || carry != 0) {
                
                int val1 = (l1 != nullptr) ? l1->val : 0;//we take value of one and value of two and add them together
                int val2 = (l2 != nullptr) ? l2->val : 0;
                
                int sum = val1 + val2 + carry;
                carry = sum / 10; // calculate carry
                
                //add the sum to the result list
                current->next = new ListNode(sum % 10);
                current = current->next;// move to the next node in the result list
                
                // Move to the next nodes in both lists, if available
                if (l1 != nullptr) l1 = l1->next;
                if (l2 != nullptr) l2 = l2->next;
            }
            // The first node is a dummy node, so we return the next node
            ListNode* finalResult = result->next;
            delete result; // Clean up the dummy node
            return finalResult;
        };
            
    };