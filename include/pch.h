/*
 * this files implement the true main function, no matter cpp file with
 * including this head file implement 'main' or not, it will work for sure by
 * class deliver. Just remember to inlcude this file before the 'main' implement
 */
#pragma once
#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include <string>
using namespace std;
function<int()> delegateMain;
template<typename T>
struct deliver
{
    int _xmain();
    operator function<int()>()
    {
        printf("declare deliver");
        return []()
        {
            return deliver<T>()._xmain();
        };
    }
};
int main(int argc, char **argv)
{
    if (delegateMain != nullptr)
        return delegateMain();
    vector<char *> vargv = {argv, argv + argc};
    char           no_catch_excepetion[] = {"--gtest_catch_exceptions=0"};
    vargv.push_back(no_catch_excepetion);
    argc++;
    ::testing::InitGoogleTest(&argc, vargv.data());
    return RUN_ALL_TESTS();
}
/*
 * instead of declare the _ABx as static to support muilti cpp feils to include
 * this, let this be global scope variable just make thing clearer
 */
#define main                                                                                                                               \
    _AB1 = 0;                                                                                                                              \
    deliver<int> __di_nouse;                                                                                                               \
    int          _AB2 = (delegateMain = deliver<int>{},0);                                                                                \
    template<>                                                                                                                             \
    int deliver<int>::_xmain
