/* 此文件从template.cpp */
#include <bits/stdc++.h>
#include <gtest/gtest.h>
#include <string>
using namespace std;

/* utils */
#include <util/util.h>
using namespace LT_UTIL; /* 这可能与一些类型不兼容，那么你需要重写类型，然后 using yourtype; */

#undef LOCAL/* 关闭引入的源文件中的local内容 */
#include <../@CPP_SOURCE_FILE@>


TEST(test,default)
{
    Solution s;
}

int main(int argc,char**argv){
    
  vector<char *> vargv = {argv, argv + argc};
  char no_catch_excepetion[]={"--gtest_catch_exceptions=0"};
  vargv.push_back(no_catch_excepetion);
  argc++;
  ::testing::InitGoogleTest(&argc, vargv.data());
  return RUN_ALL_TESTS();
}