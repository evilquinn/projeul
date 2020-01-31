/*
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order and each of their nodes contain a single digit.
 * Add the two numbers and return it as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * Example:
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 *
 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

/**
 *  * Definition for singly-linked list.
 */
struct ListNode
{
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
   ~ListNode()
   {
       delete next;
   }
};

std::ostream& operator<< (std::ostream& os, const ListNode* list)
{
    std::string sep = "(";
    if ( list == NULL )
    {
        os << sep;
    }
    for (; list != NULL; list = list->next )
    {
        os << sep << list->val;
        sep = " -> ";
    }
    return os << ")";
}

class solution {
public:
    int listnode_to_int(const ListNode* list)
    {
        int result = 0;
        for (int multiple = 1; list != NULL; list = list->next, multiple *= 10 )
        {
            result += ( list->val * multiple );
        }
        return result;
    }
    ListNode* int_to_listnode(int i)
    {
        if ( i == 0 )
        {
            return new ListNode(0);
        }
        ListNode* result = NULL;
        ListNode* n = NULL;
        ListNode* p = NULL;
        while ( i > 0 )
        {
            p = n;
            n = new ListNode(i % 10);
            if ( !result )
            {
                result = n;
            }
            else
            {
                p->next = n;
            }
            i /= 10;
        }
        return result;
    }
    ListNode* add_two_numbers(ListNode* l1, ListNode* l2)
    {

        return int_to_listnode(listnode_to_int(l1) + listnode_to_int(l2));
    }
};

int main()
{
 //* Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 //* Output: 7 -> 0 -> 8
    ListNode* l1 = solution().int_to_listnode(342);
    ListNode* l2 = solution().int_to_listnode(465);
    ListNode* result = solution().add_two_numbers(l1, l2);
    std::cout << "l1: " << l1 << ", as int: " << solution().listnode_to_int(l1) << std::endl;
    std::cout << "l2: " << l2 << ", as int: " << solution().listnode_to_int(l2) << std::endl;
    std::cout << "re: " << result << ", as int: " << solution().listnode_to_int(result) << std::endl;
    delete l1;
    delete l2;
    delete result;
}
