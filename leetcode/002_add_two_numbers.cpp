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
#include <memory>

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
        ListNode* result = l1;
        while( l1 != NULL )
        {
            if ( l2 )
            {
                l1->val += l2->val;
                if ( !l1->next ) { std::swap(l1->next, l2->next); }
                l2 = l2->next;
            }
            if ( l1->val >= 10 )
            {
                l1->val -= 10;
                if ( l1->next )
                {
                    ++l1->next->val;
                }
                else
                {
                    l1->next = new ListNode(1);
                    break;
                }
            }
            l1 = l1->next;
        }
        return result;
    }
};

int main()
{
    std::vector<std::pair<int, int> > nums = { { 342, 465 }, { 0, 37 }, { 1, 99 }, { 1, 999 } };
    for ( auto&& num : nums )
    {
        std::unique_ptr<ListNode> l1(solution().int_to_listnode(num.first));
        std::unique_ptr<ListNode> l2(solution().int_to_listnode(num.second));
        std::cout << "l1: " << l1.get() << ", as int: " << solution().listnode_to_int(l1.get()) << std::endl;
        std::cout << "l2: " << l2.get() << ", as int: " << solution().listnode_to_int(l2.get()) << std::endl;
        ListNode* result = solution().add_two_numbers(l1.get(), l2.get());
        std::cout << "re: " << result << ", as int: " << solution().listnode_to_int(result) << std::endl;
    }
}
