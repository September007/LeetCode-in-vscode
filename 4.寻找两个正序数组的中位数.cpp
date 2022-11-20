/*
 * @lc app=leetcode.cn id=4 lang=cpp
 *
 * [4] 寻找两个正序数组的中位数
 */
#include <vector>
#include <limits>
using namespace std;
// @lc code=start
class Solution
{
public:
    double findMedianSortedArrays(vector<int> &l, vector<int> &r)
    {
        if (l.size() < r.size())
            l.swap(r);
        int sum = l.size() + r.size(), needL = (sum + 1) / 2;
        int ll = 0, lr = l.size() - 1;
        l.push_back(std::numeric_limits<int>::max());
        while (l < r) //[l,r]
        {
            int m = ll + ((lr - ll) << 1);
            auto rm = std::lower_bound(r.begin(), r.end(), l[m]);
            auto rmp = std::lower_bound(r.begin(), r.end(), l[m + 1]);
            int cm = m + (rm - r.begin());
            int cmp = (rmp - r.begin());
            if (cm > needL)
                lr = m - 1;
            else if (cm == needL)
                return l[m];
            else if (cmp <= needL)
                ll = m + 1;
            else
            {
                return r[needL - (m + 1) - 1];
            }
        }
        return -1;
    }
};
// @lc code=end


int main(){
    
}
