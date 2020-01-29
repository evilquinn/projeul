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

std::ostream& operator<< (std::ostream& os, const std::vector<int>& elements)
{
    std::string sep = "[";
    for ( const auto& element : elements )
    {
        os << sep << element;
        sep = ", ";
    }
    if ( elements.empty() )
    {
        os << sep;
    }
    return os << "]";
}

/**
 *  * Definition for singly-linked list.
 */
struct ListNode
{
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

class solution {
public:
     ListNode* add_two_numbers(ListNode* l1, ListNode* l2)
     {
     }
};

int main()
{
    ListNode l1(3);
    ListNode l2(2);
    auto result = solution().add_two_numbers(&l1, &l2);
    std::cout << "result: " << ( result == NULL ) << std::endl;
}
