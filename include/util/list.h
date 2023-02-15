#pragma once
#include <vector>

namespace LT_UTIL
{
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr)
    {
    }
    ListNode(int x) : val(x), next(nullptr)
    {
    }
    ListNode(int x, ListNode *next) : val(x), next(next)
    {
    }
};

ListNode *V2L(std::vector<int> v)
{
    if(v.size()==0)return 0;
    ListNode ret {-1, 0};
    auto p = &ret;
    for (auto i : v)
    {
        p->next = new ListNode(i, 0);
        p = p->next;
    }
    return ret.next;
}

std::vector<int> L2V(ListNode *l)
{
    std::vector<int> ret;
    while (l)
    {
        ret.push_back(l->val);
        l = l->next;
    }
    return ret;
}

} // namespace LT_UTIL